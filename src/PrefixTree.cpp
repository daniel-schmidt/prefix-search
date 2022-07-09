#include "PrefixTree.h"

#include <algorithm>
#include <future>
#include <thread>

namespace TreeSearch
{
    namespace 
    {
        // Adds the given <word> to the given <tree>, recursing down existing paths 
        // and adding new nodes if necessary.
        void AddWord(NodeContainer & tree, std::string_view word) 
        {
            if(word.empty()) {
                return;
            }
            char firstChar = word[0];

            auto existingNodeIt = std::find_if(tree.begin(), tree.end(), [&](Node const & node){ 
                return node.content == firstChar;
            });

            if(existingNodeIt == tree.end()) {
                NodeContainer newSubtree{};
                AddWord(newSubtree, word.substr(1));
                tree.emplace_back(firstChar, std::move(newSubtree));
            }
            else {
                AddWord(existingNodeIt->children, word.substr(1));
            }
        };


        // Creates a subtree containing all words starting with some specific letters, depending on the <taskID>.
        struct CreateSubtree
        {
            NodeContainer operator()(size_t taskID) const
            {
                NodeContainer subTree{};
                std::for_each(wordList.cbegin(), wordList.cend(), [&](std::string_view word) {
                    if(!word.empty() && (word[0] - 'A') % numTasks == taskID) {
                        AddWord(subTree, word);
                    }
                });
                return subTree;
            }

            std::vector<std::string> const & wordList;
            size_t numTasks;
        };


        // Visitor for depth-first search, collecting all words at the leaf nodes.
        struct Serialize
        {
            Serialize(std::string_view globalPrefix)
            : curWord(globalPrefix)
            {}

            void OnNode(Node const & node)
            {
                curWord += node.content;
            }

            void OnLeaf()
            {
                words.push_back(curWord);
            }

            void FinishNode()
            {
                curWord = curWord.substr(0, curWord.size()-1);
            }

            std::string curWord;
            std::vector<std::string> words{};
        };

        // Performs a recursive depth-first visit starting with the given nodes.
        // Calls specific functions of the visitor during the traversal of the tree.
        template<typename Visitor>
        void DepthFirstVisit(NodeContainer const & tree, Visitor & visitor)
        {
            for(Node const & node: tree) {
                visitor.OnNode(node);
                if(node.children.empty()) {
                    visitor.OnLeaf();
                }
                else {
                    DepthFirstVisit(node.children, visitor);
                }
                visitor.FinishNode();
            }
        }
    }


    NodeContainer VecToTree(std::vector<std::string> const & wordList, size_t numProcs)
    {
        CreateSubtree create{ wordList, numProcs };
        using TaskType = std::packaged_task<NodeContainer(size_t)>;
        std::vector<TaskType> tasks{numProcs};
        for(auto & task : tasks) {
            task = TaskType{create};
        }

        std::vector<std::future<NodeContainer>> subtrees;
        std::transform(tasks.begin(), tasks.end(), std::back_inserter(subtrees), [](auto & task) {
            return task.get_future();
        });

        for(size_t i = 0; i < numProcs; i++) {
            std::thread t1(std::move(tasks[i]), i);
            t1.detach();
        }

        NodeContainer tree;
        for(auto & subtreeFuture : subtrees) {
            NodeContainer subtree = subtreeFuture.get();
            tree.insert(tree.end(), subtree.begin(), subtree.end());
        }
        return tree;
    }

    std::vector<std::string> TreeToVec(std::string_view prefix, NodeContainer const & tree)
    {
        Serialize serialize{ prefix };
        DepthFirstVisit(tree, serialize);
        return serialize.words;
    }
}
#include "Find.h"

#include "PrefixTree.h"

#include <algorithm>
#include <future>
#include <thread>

namespace TreeSearch
{
    struct GetMatchingChildren
    {
        NodeContainer const * operator()()
        {
            for(size_t i = taskID; i < currentLevel.size(); i += numTasks) {
                if(currentLevel[i].content == charToFind) {
                    return &currentLevel[i].children;
                }
            }
            return nullptr;
        }

        NodeContainer const & currentLevel;
        char const charToFind;
        size_t taskID;
        size_t numTasks;
    };

    NodeContainer Find(std::string_view prefix, NodeContainer const & tree, size_t numTasks)
    {
        NodeContainer const * currentLevel = &tree;
        for(char c : prefix) {
            using TaskType = std::packaged_task<NodeContainer const *()>;
            std::vector<TaskType> tasks;
            for(size_t taskID = 0; taskID < numTasks; taskID++) {
                tasks.emplace_back(GetMatchingChildren{*currentLevel, c, taskID, numTasks});
            }

            std::vector<std::future<NodeContainer const *>> possibleNextLevels;
            std::transform(tasks.begin(), tasks.end(), std::back_inserter(possibleNextLevels), [](auto & task) {
                return task.get_future();
            });

            for(auto & task : tasks) {
                std::thread t{std::move(task)};
                t.detach();
            }
            
            for(auto & subtreeFuture : possibleNextLevels) {
                NodeContainer const * subtree = subtreeFuture.get();
                if(subtree) {
                    currentLevel = subtree;
                }
            }

        }
        return *currentLevel;
    }
}
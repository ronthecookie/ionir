#include <ionir/passes/pass.h>
#include "pch.h"

using namespace ionir;

TEST(PassManagerTest, InitializeEmpty) {
    PassManager passManager = PassManager();

    EXPECT_TRUE(passManager.getPasses().empty());
}

TEST(PassManagerTest, Initialize) {
    PassManager passManager = PassManager({
        PassManager::Item{}
    });

    EXPECT_FALSE(passManager.getPasses().empty());
}

TEST(PassManagerTest, GetPasses) {
    PassManager::Item passItem = PassManager::Item{};

    PassManager passManager = PassManager({
        passItem
    });

//    auto passes = passManager.getPasses();
//
//    EXPECT_EQ(passes.size(), 1);
//
//    PassManager::Item firstPassItem = passes[0];
//
//    EXPECT_EQ(firstPassItem.priority, passItem.priority);
//    EXPECT_EQ(firstPassItem.pass, passItem.pass);
}

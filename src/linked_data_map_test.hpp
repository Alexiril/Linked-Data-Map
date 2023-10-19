#pragma once
#ifndef LINKED_DATA_MAP_TEST_HPP
#define LINKED_DATA_MAP_TEST_HPP

#include <string>

using std::string;

#include "gtest/gtest.h"
#include "benchmark/benchmark.h"
#include "linked_data_map.hpp"

namespace LDM {
    namespace LDMTests {

        class LDMTest : public testing::Test {
        protected:
            void SetUp() override;
            void TearDown() override;

            unique_ptr< LDM <string>> map_;
        };
        
    }
}

#endif // !LINKED_DATA_MAP_TEST_HPP
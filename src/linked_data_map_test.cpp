#include "linked_data_map_test.hpp"

namespace LDM::LDMTests {

    void LDMTest::SetUp() {
        map_.reset(new LDM<string>());
    }

    void LDMTest::TearDown() {
        map_.reset();
    }

    TEST_F(LDMTest, EmptySize) {
        ASSERT_EQ(map_->empty(), true);
        ASSERT_EQ(map_->size(), 0);
    }

}


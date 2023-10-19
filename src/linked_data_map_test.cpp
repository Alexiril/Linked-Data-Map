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

    TEST_F(LDMTest, AddRemoveGetLinked) {
        ASSERT_NO_THROW(map_->add_linked("a", "b"));
        ASSERT_EQ((*map_)["a"]->size(), 2);
        ASSERT_EQ(map_->are_linked("a", "b"), true);
        ASSERT_EQ(map_->are_linked("b", "d"), false);
        ASSERT_EQ(map_->size(), 2);
        ASSERT_NO_THROW(map_->add_linked("b", "c"));
        ASSERT_EQ(map_->size(), 3);
        ASSERT_EQ(map_->are_linked("a", "c"), true);
        ASSERT_EQ(map_->empty(), false);
        ASSERT_NO_THROW(map_->remove_linked("b"));
        ASSERT_EQ(map_->size(), 2);
        ASSERT_EQ(map_->are_linked("a", "b"), false);
        ASSERT_EQ(map_->are_linked("a", "c"), true);
        ASSERT_ANY_THROW(map_->at("b"));
        ASSERT_NO_THROW(map_->add_linked("d", "a"));
        ASSERT_EQ(map_->size(), 3);
        ASSERT_EQ(map_->are_linked("c", "d"), true);
        ASSERT_NO_THROW(map_->remove_linked("c"));
        ASSERT_EQ(map_->size(), 2);
        ASSERT_NO_THROW(map_->remove_linked("d"));
        ASSERT_EQ(map_->empty(), true);
        ASSERT_EQ(map_->size(), 0);
        ASSERT_ANY_THROW(map_->at("a"));
    }

    TEST_F(LDMTest, MergeClasters) {
        ASSERT_NO_THROW(map_->add_linked("a", "b"));
        ASSERT_NO_THROW(map_->add_linked("a", "c"));
        ASSERT_NO_THROW(map_->add_linked("d", "e"));
        ASSERT_NO_THROW(map_->add_linked("d", "f"));
        ASSERT_EQ(map_->get_clasters(), 2);
        ASSERT_NO_THROW(map_->add_linked("a", "d"));
        ASSERT_NO_THROW(map_->add_linked("a", "b"));
        ASSERT_EQ(map_->get_clasters(), 1);
        ASSERT_NO_THROW(map_->clear());
        ASSERT_EQ(map_->size(), 0);
    }

    static void BM_Standard(benchmark::State& state) {
        auto map_ = LDM<u64>();
        for (auto _ : state)
        {
            u64 i = 1;
            for (; i < 1000000; ++i)
                map_.add_linked(i - 1, i);
            for (; i > 0; --i)
                map_.remove_linked(i);
        }
    }
    BENCHMARK(BM_Standard);

    static void BM_ManyClasters(benchmark::State& state) {
        auto map_ = LDM<u64>();
        for (auto _ : state)
        {
            u64 i = 1;
            for (; i < 1000000; i += 2)
                map_.add_linked(i - 1, i);
            for (; i > 0; --i)
                map_.remove_linked(i);
        }
    }
    BENCHMARK(BM_ManyClasters);

    static void BM_MergeClasters(benchmark::State& state) {
        auto map_ = LDM<u64>();
        for (auto _ : state)
        {
            u64 i = 1;
            for (; i < 500000; i += 2) {
                map_.add_linked(i - 1, i);
                if (i > 1) map_.add_linked(i - 2, i);
            }
            for (; i > 0; --i)
                map_.remove_linked(i);
        }
    }
    BENCHMARK(BM_MergeClasters);

    static void BM_Clear(benchmark::State& state) {
        auto map_ = LDM<u64>();
        for (auto _ : state)
        {
            u64 i = 1;
            for (; i < 1000000; ++i)
                map_.add_linked(i - 1, i);
            map_.clear();
        }
    }
    BENCHMARK(BM_Clear);

    TEST(LDMTestBM, Benchmarks)
    {
        benchmark::RunSpecifiedBenchmarks();
        benchmark::Shutdown(); 
    }

}


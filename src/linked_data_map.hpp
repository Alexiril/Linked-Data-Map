#pragma once
#ifndef LINKED_DATA_MAP_HPP
#define LINKED_DATA_MAP_HPP

#include "shared.hpp"

namespace LDM {

    template <typename T> class LDM {
        
    private:
        unique_ptr<map<T, shared_ptr<set<T>>>> map_;

    public:

        inline LDM() {
            map_.reset(new map<T, shared_ptr<set<T>>>());
        }

        LDM(const LDM<T> & value) {
            for (auto& [key, ptr] : *value.map_)
                (*map_)[key].reset(new set<T>(*ptr));
        }

        LDM(LDM<T> && value) : map_(std::move(value.map_)) {}
        
        ~LDM() {
            clear();
        }

        const shared_ptr<set<T>> & operator[] (const T & index) const { return (*map_)[index]; }

        const shared_ptr<set<T>> & at (const T & index) const { return map_->at(index); }

        void add_linked(const T & first, const T & second) {
            auto data = *map_;

            bool cont_first = data.contains(first);
            bool cont_second = data.contains(second);

            // Create new claster of linked data
            if (not cont_first and not cont_second) {
                data[first].reset(new set<T>());
                data[first]->insert(first);
                data[second] = data[first];
                data[first]->insert(second);
                return;
            }

            // Add a value to an exist claster
            if ((cont_first and not cont_second) or (not cont_first and cont_second)) {
                if (cont_first) {
                    data[first]->insert(second);
                    data[second] = data[first];
                }
                if (cont_second) {
                    data[second]->insert(first);
                    data[first] = data[second];
                }
                return;
            }

            // Merging clasters
            if (cont_first and cont_second) {
                // Find smaller claster
                bool first_smaller = data[first]->size() < data[second]->size();
                shared_ptr<set<T>> claster = first_smaller ? data[first] : data[second];
                const T& bigger_key = first_smaller ? second : first;

                // Insert elems from smaller claster set to bigger
                data[bigger_key]->insert(claster->begin(), claster->end());

                // Change claster in elems from smaller claster set
                for (auto& key : *claster)
                    data[key] = data[bigger_key];

                claster.reset();
            }
        }

        void remove_linked(const T & value) {
            auto data = *map_;

            if (not data.contains(value)) return;

            // Removing claster
            if (data[value]->size() <= 2) {
                shared_ptr<set<T>> claster = data[value];
                for (auto& key : *claster)
                    data.erase(data.find(key));
                claster.reset();
                return;
            }

            // Removing only one element from claster
            {
                shared_ptr<set<T>> claster = data[value];
                data.erase(data.find(value));
                claster->erase(claster->find(value));
            }
        }

        u64 size() const { return map_->size(); }
        
        u64 count_linked(const T & value) const {
            if (not map_->contains(value)) return 0;
            return (*map_)[value]->size();
        }

        bool are_linked(const T & first, const T & second) const {
            auto data = *map_;

            if (not data.contains(first) or not data.contains(second))
                return false;
            return data[first] == data[second];
        }

        void clear() { map_.reset(); }

        bool empty() const { return map_->empty(); }
    };

}

#endif // !LINKED_DATA_MAP_HPP
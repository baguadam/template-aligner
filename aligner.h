#ifndef _ALIGNER_H_
#define _ALIGNER_H_

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

template <typename T>
class aligner {
    protected:
        std::vector<std::vector<T>*> added_vectors;
        size_t max_length;
        bool is_filler_set;
        T filler;
        int count_vectors;

    public:
        aligner() : added_vectors(0), max_length(0), is_filler_set(false), count_vectors(0) { }
        virtual ~aligner() { count_vectors = 0; }  

        virtual void align() = 0;
        void set_filler(T _filler) { 
            filler = _filler; 
            is_filler_set = true;
        }

        void add(std::vector<T> &vec) {
            ++count_vectors;
            if (vec.size() > max_length) {
                max_length = vec.size();
            }
            added_vectors.push_back(&vec);
        }
        
        int count() { return count_vectors; }
        int get_max_length() { return max_length; }
};
kiskutya

template <typename T>
class center_aligner : public aligner<T> {
    public:
        void align() {
            for (int i = 0; i < aligner<T>::count_vectors; ++i) {
                size_t size = aligner<T>::added_vectors[i]->size();
                if (size < aligner<T>::max_length) {
                    int start = floor((aligner<T>::max_length - size)/2);
                    std::vector<T> vec_temp(aligner<T>::max_length);
                    if (aligner<T>::is_filler_set) {
                        std::fill(vec_temp.begin(), vec_temp.end(), aligner<T>::filler);
                    }
                    std::copy(aligner<T>::added_vectors[i]->begin(), aligner<T>::added_vectors[i]->end(), vec_temp.begin() + start);
                    *aligner<T>::added_vectors[i] = vec_temp;
                }
            }
        }
};
sfdgdsfgsdf
sdfgsdfgsdfsdfgsdfg
sdfgsdfgsdfg
sdfgsdfgsdfgsdfg
template <typename T>
class left_aligner : public aligner<T> {
    public:
        void align() {
            for (int i = 0; i < aligner<T>::count_vectors; ++i) {
                size_t size = aligner<T>::added_vectors[i]->size();
                if (size < aligner<T>::max_length) {
                    if (aligner<T>::is_filler_set) {
                        aligner<T>::added_vectors[i]->resize(aligner<T>::max_length, aligner<T>::filler);
                    } else {
                        aligner<T>::added_vectors[i]->resize(aligner<T>::max_length);
                    }
                }
            }   
        }
};

template <typename T>
class right_aligner : public aligner<T> {
    public:
        void align() {
            for (int i = 0; i < aligner<T>::count_vectors; ++i) {
                size_t size = aligner<T>::added_vectors[i]->size();
                if (size < aligner<T>::max_length) {
                    std::vector<T> vec_temp(aligner<T>::max_length - size);
                    if (aligner<T>::is_filler_set) {
                        std::fill(vec_temp.begin(), vec_temp.end(), aligner<T>::filler);
                    }
                    std::copy(aligner<T>::added_vectors[i]->begin(), aligner<T>::added_vectors[i]->end(), std::back_inserter(vec_temp));
                    *aligner<T>::added_vectors[i] = vec_temp;
                }
            }
        }
};

#endif
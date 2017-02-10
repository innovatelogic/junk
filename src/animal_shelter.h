#pragma once

#include "defexport.h"
#include <list>

namespace junk
{
    namespace animal_shelter
    {
        class JUNK_EXPORT Animal
        {
        public:
            Animal()
                : m_order(0)
            {}

            virtual ~Animal()
            {}
            
            int order() const { return m_order; }
            void set_order(int order) { m_order = order;  }

        private:
            int m_order;
        };

        class JUNK_EXPORT Cat : public Animal
        {
        public:
            Cat()
            {}
        };

        class JUNK_EXPORT Dog : public Animal
        {
        public:
            Dog()
            {}
        };

        class JUNK_EXPORT AnimalShelter
        {
        public:
            AnimalShelter()
                : m_dogs(new std::list<Animal*>())
                , m_cats(new std::list<Animal*>())
                , m_order(0)
            {}

            virtual ~AnimalShelter()
            {
                delete m_dogs;
                delete m_cats;
            }

            void enqueue(Animal *animal)
            {
                if (animal)
                {
                    if (dynamic_cast<Dog*>(animal) != nullptr)
                    { 
                        AddDog(animal);
                    }
                    else if (dynamic_cast<Cat*>(animal) != nullptr)
                    {
                        AddCat(animal);
                    }
                    else
                    {
                        throw;
                    }
                }
            }

            Animal* dequeueDog()
            {
                Animal *out = nullptr;
                if (!m_dogs->empty())
                {
                    out = *(m_dogs->rbegin());
                    m_dogs->remove(out);
                }
                return out;
            }

            Animal* dequeueCat()
            {
                Animal *out = nullptr;
                if (!m_cats->empty())
                {
                    out = *(m_cats->rbegin());
                    m_cats->remove(out);
                }
                return out;
            }

            Animal* dequeue()
            {
                if (m_dogs->empty()) {
                    return dequeueCat();
                }

                if (m_cats->empty()){
                    return dequeueDog();
                }

                Animal *out = nullptr;

                Animal *dog = *(m_dogs->rbegin());
                Animal *cat = *(m_cats->rbegin());

                // get oldest
                if (dog->order() < cat->order()) // dog is older
                {
                    out = dog;
                    m_dogs->remove(out);
                }
                else
                {
                    out = cat;
                    m_cats->remove(out);
                }
                return out;
            }

        protected:
            void AddDog(Animal *animal)
            {
                if (animal) { // TODO: check to avoid add twice
                    
                    animal->set_order(m_order++);
                    m_dogs->push_front(animal);
                }
            }

            void AddCat(Animal *animal)
            {
                if (animal) { // TODO: check to avoid add twice
                    animal->set_order(m_order++);
                    m_cats->push_front(animal);
                }
            }
        private:
            std::list<Animal*> *m_dogs;
            std::list<Animal*> *m_cats;
            int m_order;
        };
    }
}
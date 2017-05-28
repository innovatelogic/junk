#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace animal_shelter
    {
        TEST(Design, AnimalShelter_PushPopAnimal)
        {
            AnimalShelter shelter;

            Cat * cat0 = new Cat();
            Dog * dog1 = new Dog();
            Dog * dog2 = new Dog();
            Cat * cat3 = new Cat();

            shelter.enqueue(cat0);
            shelter.enqueue(dog1);
            shelter.enqueue(dog2);
            shelter.enqueue(cat3);

            Animal * out = shelter.dequeueDog();
            EXPECT_EQ(out, dog1);

            out = shelter.dequeue();
            EXPECT_EQ(out, cat0);

            out = shelter.dequeueCat();
            EXPECT_EQ(out, cat3);

            out = shelter.dequeue();
            EXPECT_EQ(out, dog2);

            EXPECT_EQ(nullptr, shelter.dequeue());
            EXPECT_EQ(nullptr, shelter.dequeueDog());
            EXPECT_EQ(nullptr, shelter.dequeueCat());

            delete cat0;
            delete dog1;
            delete dog2;
            delete cat3;
        }
    }
}
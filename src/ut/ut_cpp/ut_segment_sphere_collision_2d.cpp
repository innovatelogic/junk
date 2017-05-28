#include "cpp.h"

#include <gtest/gtest.h>

namespace junk
{
	namespace segment_sphere_colision_2d
	{
        TEST(Math, SegmentSphereCollisionIntersection)
        {
            // player - player position
            // enemy - enemy position
            // hit_to - enemy point to fire
            // rad - radius
             
            {
                Vector player(0.f, 0.f, 0.f),
                    hit_to(0.f, 10.f, 0.f),
                    enemy(0.f, 10.f, 0.f);
                float rad = 0.5f;

                float mu1, mu2;
                EXPECT_TRUE(SegmentSphereIntersection<void>(player, hit_to, enemy, fabs(rad), &mu1, &mu2));
            }

            {
                Vector player(0.f, 0.f, 0.f),
                    hit_to(0.f, -10.f, 0.f),
                    enemy(0.f, 10.f, 0.f);
                float rad = 0.5f;

                float mu1, mu2;
                EXPECT_FALSE(SegmentSphereIntersection<void>(player, hit_to, enemy, fabs(rad), &mu1, &mu2));
            }

            {
                Vector player(0.f, 0.f, 0.f),
                    hit_to(0.7f, 10.0f, 0.f),
                    enemy(0.f, 10.f, 0.f);
                float rad = 0.5f;

                float mu1, mu2;
                EXPECT_FALSE(SegmentSphereIntersection<void>(player, hit_to, enemy, fabs(rad), &mu1, &mu2));
            }
        }
	}
}
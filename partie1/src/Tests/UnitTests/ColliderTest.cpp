/*
 * prjsv 2016
 * 2016
 * Marco Antognini
 */

#include <Application.hpp>
#include <Obstacle/CircularCollider.hpp>

#include <catch.hpp>
//#include <extlib/Catch/include/catch.hpp>

#include <iostream>

// Create a dummy CircularCollider subclass
class Body : public CircularCollider
{
public:
    Body(Vec2d const& position, double radius)
        : CircularCollider(position, radius)
    {
    }
};

SCENARIO("Collision/IsCircularColliderInside with CircularCollider", "[Body]")
{
    GIVEN("Two identical bodies") {
        auto b1 = Body({ 1, 1 }, 2);
        auto b2 = b1;

        THEN("they collide") {
            std::cout << b1 << std::endl;

            CHECK(b1.isColliding(b2));
            CHECK(b2.isColliding(b1));
            CHECK((b1 | b2));
            CHECK((b2 | b1));
        }

        THEN("they are inside of each other") {
            CHECK(b1.isCircularColliderInside(b2));
            CHECK(b2.isCircularColliderInside(b1));
            CHECK(b1 > b2);
            CHECK(b2 > b1);
        }
    }

    GIVEN("Two bodies that don't overlap") {
        auto b1 = Body({ 1, 1 }, 0.5);
        auto b2 = Body({ -1, -1 }, 0.5);

        THEN("they don't collide") {
            CHECK_FALSE(b1.isColliding(b2));
            CHECK_FALSE(b2.isColliding(b1));
            CHECK_FALSE((b1 | b2));
            CHECK_FALSE((b2 | b1));
        }

        AND_THEN("they are not inside of each other") {
            CHECK_FALSE(b1.isCircularColliderInside(b2));
            CHECK_FALSE(b2.isCircularColliderInside(b1));
            CHECK_FALSE(b1 > b2);
            CHECK_FALSE(b2 > b1);
        }
    }

    GIVEN("Two bodies that overlap but are not inside of each other") {
        auto b1 = Body({ 0, 0 }, 2);
        auto b2 = Body({ 3, 0 }, 2);

        THEN("they collide") {
            CHECK(b1.isColliding(b2));
            CHECK(b2.isColliding(b1));
            CHECK((b1 | b2));
            CHECK((b2 | b1));
        }

        THEN("they are not inside of each other") {
            CHECK_FALSE(b1.isCircularColliderInside(b2));
            CHECK_FALSE(b2.isCircularColliderInside(b1));
            CHECK_FALSE(b1 > b2);
            CHECK_FALSE(b2 > b1);
        }
    }

    GIVEN("A body inside another one") {
        auto b1 = Body({ 0, 0 }, 5);
        auto b2 = Body({ 0, 0 }, 1);

        THEN("they collide") {
            CHECK(b1.isColliding(b2));
            CHECK(b2.isColliding(b1));
            CHECK((b1 | b2));
            CHECK((b2 | b1));
        }

        THEN("the smaller one is inside the bigger one") {
            CHECK(b1.isCircularColliderInside(b2));
            CHECK(b1 > b2);
        }

        THEN("the bigger one is not inside the smaller one") {
            CHECK_FALSE(b2.isCircularColliderInside(b1));
            CHECK_FALSE(b2 > b1);
        }
    }

    GIVEN("A body and two points, one inside and one outside the body") {
        auto b = Body({ 0, 0 }, 5);
        auto p1 = Vec2d(0, 0);
        auto p2 = Vec2d(6, 0);

        THEN("only one point is inside") {
            CHECK(b.isPointInside(p1));
            CHECK_FALSE(b.isPointInside(p2));
            CHECK(b > p1);
            CHECK_FALSE(b > p2);
        }
    }

    GIVEN("A body") {
        auto b = Body({ 1, 2 }, 2);

        THEN("it moves correctly") {
            b.move({ 1, 0 });
            CHECK(Vec2d(2, 2) == b.getPosition());
            b += { -2, -2 };
            CHECK(Vec2d(0, 0) == b.getPosition());
        }

        THEN("it can be copied") {
            auto copy = b;
            CHECK(b.getPosition() == copy.getPosition());
            CHECK(b.getRadius() == copy.getRadius());

            auto docy = Body({ 3, 4 }, 5);
            docy = b;
            CHECK(b.getPosition() == docy.getPosition());
            CHECK(b.getRadius() == docy.getRadius());
        }
    }
}

SCENARIO("Collision/IsCircularColliderInside with CircularCollider using toric properties", "[CircularCollider]")
{
    GIVEN("A few bodies") {
        //
        // Illustration of the bodies in the world.
        // All bodies have a radius of 2.
        //
        //    4 2
        //     +---------+  --> x axis
        //    3|1       3|
        // 5   |     5   |
        //     |         |
        //     |         |
        //     |2       4|
        //     +---------+
        //
        //     |
        //     ˅
        //     y axis
        //

        REQUIRE(getAppConfig().simulation_world_size >= 10);
        REQUIRE(getAppConfig().simulation_world_size >= 10);

        auto b1 = Body({  1,  1 }, 2);
        auto b2 = Body({  1, -1 }, 2);
        auto b3 = Body({ -1,  1 }, 2);
        auto b4 = Body({ -1, -1 }, 2);
        auto b5 = Body({ -4,  2 }, 2);

        THEN("some collide, some don't") {
            CHECK(b1.isColliding(b2));
            CHECK(b2.isColliding(b1));

            CHECK(b1.isColliding(b3));
            CHECK(b3.isColliding(b1));

            CHECK(b1.isColliding(b4));
            CHECK(b4.isColliding(b1));

            CHECK(!b1.isColliding(b5));
            CHECK(!b5.isColliding(b1));

            CHECK(b2.isColliding(b3));
            CHECK(b3.isColliding(b2));

            CHECK(b2.isColliding(b4));
            CHECK(b4.isColliding(b2));

            CHECK(!b2.isColliding(b5));
            CHECK(!b5.isColliding(b2));

            CHECK(b3.isColliding(b4));
            CHECK(b4.isColliding(b3));

            CHECK(b3.isColliding(b5));
            CHECK(b5.isColliding(b3));

            CHECK(!b4.isColliding(b5));
            CHECK(!b5.isColliding(b4));
        }

        AND_THEN("none is inside another one but itself") {
            CHECK(b1.isCircularColliderInside(b1));
            CHECK(!b1.isCircularColliderInside(b2));
            CHECK(!b1.isCircularColliderInside(b3));
            CHECK(!b1.isCircularColliderInside(b4));
            CHECK(!b1.isCircularColliderInside(b5));

            CHECK(b2.isCircularColliderInside(b2));
            CHECK(!b2.isCircularColliderInside(b3));
            CHECK(!b2.isCircularColliderInside(b4));
            CHECK(!b2.isCircularColliderInside(b5));

            CHECK(b3.isCircularColliderInside(b3));
            CHECK(!b3.isCircularColliderInside(b4));
            CHECK(!b3.isCircularColliderInside(b5));

            CHECK(b4.isCircularColliderInside(b4));
            CHECK(!b4.isCircularColliderInside(b5));
        }

        AND_THEN("isPointInside works too") {
            CHECK(b1.isPointInside({ 1, 1 }));
            CHECK(b1.isPointInside({ 3, 1 }));
            CHECK(b1.isPointInside({ 2, 2 }));
            CHECK(!b1.isPointInside({ 3, 3 }));
            CHECK(b1.isPointInside({ -1, 1 }));
            CHECK(b1.isPointInside({ 1, -1 }));
            CHECK(b1.isPointInside({ -0.25, -0.25 }));
            CHECK(!b1.isPointInside({ -0.5, -0.5 }));
            CHECK(!b1.isPointInside({ -2, -2 }));
        }
    }
    GIVEN("One body inside another one") {
        // Those two bodies are colliding and the
        // second one is inside the first one because
        // the world is toric.
        auto b1 = Body({  1,  1 }, 5);
        auto b2 = Body({ -1, -1 }, 1);

        THEN("they collide and isCircularColliderInside works") {
            CHECK(b1.isColliding(b2));
            CHECK(b1.isCircularColliderInside(b2));
        }
    }

    GIVEN("One simple body") {

        REQUIRE(getAppConfig().simulation_world_size >= 10);
        REQUIRE(getAppConfig().simulation_world_size >= 10);


        //
        // Here we test distanceTo and directionTo in
        // a toric world.
        //
        //    z y
        //     +---------+  --> x axis
        //    x|bv      y|
        //     |wu       |
        //     |         |
        //     |         |
        //     |x       z|
        //     +---------+
        //
        //     |
        //     ˅
        //     y axis
        //

        auto b = Body({ 1, 1 }, 1);
        auto x = Vec2d(-1, 1);
        auto y = Body({ 1, -1 }, 1);
        auto z = Vec2d( -1, -1 );
        auto u = Body({ 2, 2 }, 1);
        auto v = Vec2d(2, 1);
        auto w = Vec2d(1, 2);

        THEN("distanceTo works") {
            CHECK(b.distanceTo(u) == Approx(std::sqrt(2)));
            CHECK(b.distanceTo(v) == Approx(1));
            CHECK(b.distanceTo(w) == Approx(1));
            CHECK(b.distanceTo(x) == Approx(2));
            CHECK(b.distanceTo(y) == Approx(2));
            CHECK(b.distanceTo(z) == Approx(std::sqrt(8)));
        }

        AND_THEN("directionTo works") {
            CHECK(b.directionTo(u) == Vec2d( 1, 1 ));
            CHECK(b.directionTo(v) == Vec2d( 1, 0 ));
            CHECK(b.directionTo(w) == Vec2d( 0, 1 ));
            CHECK(b.directionTo(x) == Vec2d( -2, 0 ));
            CHECK(b.directionTo(y) == Vec2d( 0, -2 ));
            CHECK(b.directionTo(z) == Vec2d( -2, -2 ));
        }
    }
}

#pragma once
#include "circle.hpp"
#include "structs.hpp"
#include "object.hpp"
#include <cmath>

Vector contact_normal(Circle &a, Circle &b)
{
    // calculate a direction between circles' centres
    float y{b.get_y() - a.get_y()};
    float x{b.get_x() - a.get_x()};
    float dist{std::hypot(x, y)};
    return {x / dist, y / dist};
}

Vector border_contact_normal(Direction &border)
{
    switch (border)
    {
    case Direction::Top:
        return {0, -1};
    case Direction::Right:
        return {1, 0};
    case Direction::Bottom:
        return {0, 1};
    case Direction::Left:
        return {-1, 0};
    default:
        throw std::runtime_error("Border direction has to be spcified");
    }
}

float closing_velocity(Object &a, Object &b, Vector &contact_norm_vec)
{
    // (V_a - V_b) * contact_normal
    auto velocity_delta = a.get_velocity() - b.get_velocity();
    return velocity_delta * contact_norm_vec;
}

float change_in_velocity(float velocity_before, float c)
{
    return -velocity_before * (1 + c);
}

float scalar_impulse(float velocity_change, float inverse_mass_a, float inverse_mass_b)
{
    return velocity_change / (inverse_mass_a + inverse_mass_b);
}

float scalar_impulse(float velocity_change, float inverse_mass)
{
    return velocity_change / inverse_mass;
}

Vector calc_impulse_vector(Vector &contact_normal, float scalar_impulse)
{
    return contact_normal * scalar_impulse;
}

void apply_impulse_to_velocity(Circle &circle, Vector &impulse_vector, bool reverse_direction = false)
{
    if (reverse_direction)
        impulse_vector = -impulse_vector;
    auto impulse_divided_by_mass = impulse_vector * circle.get_inverse_mass();
    auto resolution_velocity = circle.get_velocity() + impulse_divided_by_mass;
    circle.set_velocity(resolution_velocity);
}

float penetration_depth(Circle &circle, WindowSize &window, Direction &wall_direction)
{
    using enum Direction;
    switch (wall_direction)
    {
    case Top:
        return circle.get_radius() - circle.get_y();
    case Bottom:
        return circle.get_radius() - (window.height - circle.get_y());
    case Right:
        return circle.get_radius() - (window.width - circle.get_x());
    case Left:
        return circle.get_radius() - circle.get_x();
    default:
        return 0;
    }
}

float penetration_depth(Circle &a, Circle &b)
{
    float y{b.get_y() - a.get_y()};
    float x{b.get_x() - a.get_x()};
    float circle_centre_dist{std::hypot(x, y)};
    return a.get_radius() + b.get_radius() - circle_centre_dist;
}

Vector undo_penetration_vec(float mass_a, float mass_b, float penetration_depth, Vector contact_normal)
{
    return contact_normal * (mass_b / (mass_a + mass_b) * penetration_depth);
}

void resolve_interpenetration(Circle &a, Circle &b)
{
    Vector contact_normal_vec = contact_normal(a, b);
    float p_depth = penetration_depth(a, b);
    Vector unpenetrate_a = undo_penetration_vec(a.get_mass(), b.get_mass(), p_depth, -contact_normal_vec);
    Vector unpenetrate_b = undo_penetration_vec(b.get_mass(), a.get_mass(), p_depth, contact_normal_vec);
    a.move(unpenetrate_a.x, unpenetrate_a.y);
    b.move(unpenetrate_b.x, unpenetrate_b.y);
}

void resolve_interpenetration(Circle &circle, WindowSize &window, Direction &wall_direction)
{
    Vector contact_normal = border_contact_normal(wall_direction);
    float p_depth = penetration_depth(circle, window, wall_direction);
    Vector move_vector = -contact_normal * p_depth;
    std::cout << "before pen resolution: " << circle.get_position() << "\n";
    circle.move(move_vector.x, move_vector.y);
    std::cout << "after pen resolution: " << circle.get_position() << "\n";
}

void resolve_collision(Circle &a, Circle &b)
{
    // coefficient of restitution
    float c = 1;
    auto contact_normal_vec = contact_normal(a, b);
    auto closing_vel = closing_velocity(a, b, contact_normal_vec);
    auto velocity_change = change_in_velocity(closing_vel, c);
    float impulse_strength = scalar_impulse(velocity_change, a.get_inverse_mass(), b.get_inverse_mass());
    auto impulse_vector = calc_impulse_vector(contact_normal_vec, impulse_strength);
    apply_impulse_to_velocity(a, impulse_vector);
    apply_impulse_to_velocity(b, impulse_vector, true);
    resolve_interpenetration(a, b);
}

void resolve_border_collision(Circle &circle, Direction &border_direction, WindowSize &window)
{
    float c = 1;
    Object border;
    Vector contact_normal_vec = border_contact_normal(border_direction);
    float closing_vel = closing_velocity(circle, border, contact_normal_vec);
    float velocity_change = change_in_velocity(closing_vel, c);
    float impulse_strength = scalar_impulse(velocity_change, circle.get_inverse_mass());
    Vector impulse_vector = calc_impulse_vector(contact_normal_vec, impulse_strength);
    apply_impulse_to_velocity(circle, impulse_vector);
    resolve_interpenetration(circle, window, border_direction);
}
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

float closing_velocity(Object &a, Object &b, Vector &contact_norm_vec)
{
    // (V_a - V_b) * contact_normal
    auto velocity_delta = a.get_velocity() - b.get_velocity();
    std::cout << "velocity_delta: " << velocity_delta << "\n";
    std::cout << "contact_norm_vec: " << contact_norm_vec << "\n";
    return velocity_delta * contact_norm_vec;
}

float change_in_velocity(float velocity_before, float c)
{
    return -velocity_before * (1 + c);
}

float scalar_impulse(float velocity_change, float inverse_mass_a, float inverse_mass_b)
{
    return velocity_change /  (inverse_mass_a + inverse_mass_b);
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
    std::cout << "new_velocity: " << resolution_velocity << "\n";
    circle.set_velocity(resolution_velocity);
}

void resolve_collision(Circle &a, Circle &b)
{
    // coefficient of restitution
    float c =0.9;
    auto contact_normal_vec = contact_normal(a, b);
    auto closing_vel = closing_velocity(a, b, contact_normal_vec);
    auto velocity_change = change_in_velocity(closing_vel, c);
    float impulse_strength = scalar_impulse(velocity_change, a.get_inverse_mass(), b.get_inverse_mass());
    std::cout << "impulse strength: " << impulse_strength << "\n";
    auto impulse_vector = calc_impulse_vector(contact_normal_vec, impulse_strength);
    std::cout << "impulse_vector: " << impulse_vector << "\n";
    apply_impulse_to_velocity(a, impulse_vector);
    apply_impulse_to_velocity(b, impulse_vector, true);
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

void resolve_border_collision(Circle &circle, Direction &border_direction)
{
    float c = 1.1;
    Object border;
    Vector contact_normal_vec = border_contact_normal(border_direction);
    float closing_vel = closing_velocity(circle, border, contact_normal_vec);
    float velocity_change = change_in_velocity(closing_vel, c);
    float impulse_strength = scalar_impulse(velocity_change, circle.get_inverse_mass());
    Vector impulse_vector = calc_impulse_vector(contact_normal_vec, impulse_strength);
    apply_impulse_to_velocity(circle, impulse_vector);
}
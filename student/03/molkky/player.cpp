#include "player.hh"
#include <iostream>
#include <string>

Player::Player(const std::string &name):
    name_(name),
    points_(0)
{

}

std::string Player::get_name()
{
    return name_;
}

int Player::get_points()
{
    return points_;
}

bool Player::has_won()
{
    if ( points_ == 50)
    {
        return true;
    }
    return false;
}

void Player::add_points(int points)
{
    if (points + points_ <= 50)
    {
      points_ += points;
      return;
    }
    std::cout << name_ << " gets penalty points!" << std::endl;
    points_ = 25;
}

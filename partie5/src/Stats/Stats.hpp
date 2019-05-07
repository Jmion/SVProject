//
// Created by jeremy on 5/7/19.
//

#ifndef PARTIE1_STATS_HPP
#define PARTIE1_STATS_HPP


#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Utility/Vec2d.hpp>
#include "Graph.hpp"
#include <unordered_map>



class Stats {

    /*!
     * Graph number to draw
     */
    int actif;

    /*!
     * Graphs being tracked by this.
     */
    std::unordered_map<int,std::unique_ptr<Graph>> graphs;

    /*!
     * Labels for graphs
     */
    std::unordered_map<int,std::string> labels;

public:
    void setActif(int actif);

    int getActif() const;

    void update(sf::Time dt);

    void reset();

    void draw(sf::RenderTarget & target) const;

    void addGraph(int currentGraphId, std::string const& title, std::vector<std::string> const& series, double min, double max, Vec2d statSize);

    void focusOn(std::string title);

};


#endif //PARTIE1_STATS_HPP

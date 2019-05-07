//
// Created by jeremy on 5/7/19.
//

#include "Stats.hpp"
#include "Graph.hpp"
#include <unordered_map>
#include <memory>

int Stats::getActif() const {
    return actif;
}

void Stats::setActif(int actif) {
    Stats::actif = actif;
}


void Stats::update(sf::Time dt) {
    //TODO
}

void Stats::reset() {
    for (auto it = graphs.begin(); it != graphs.end(); it++) {
        it->second.reset();
    }
}

void Stats::draw(sf::RenderTarget & target) const {
    auto it = graphs.find(actif);
    if (it != graphs.end()) {
        graphs.at(actif)->draw(target);
    }
}

void Stats::addGraph(int currentGraphId, std::string const &title, std::vector<std::string> const &series, double min,
                     double max, Vec2d statSize) {
    auto it = graphs.find(currentGraphId);
    if (it == graphs.end()) {
        graphs.insert(std::pair<int, std::unique_ptr<Graph>>(currentGraphId,std::unique_ptr<Graph>(new Graph(series,statSize,min,max))));
    }else{
        graphs.at(currentGraphId).reset(new Graph(series,statSize,min,max));
    }
    actif = currentGraphId;
}

void Stats::focusOn(std::string title) {
//TODO
}



#include <SDL2/SDL.h>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <chrono>
#include "pugixml.hpp"
#include "haversine.h"
#include "shortestpath.h"

int main()
{

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("../resources/exportLarge.osm");
    if (!result)
    {
        return -1;
    }

    pugi::xml_node osm = doc.child("osm");

    int i = 0;
    Graph g;
    for (pugi::xml_node node : osm.children("node"))
    {
        i++;
        long id = node.attribute("id").as_llong();
        double lat = node.attribute("lat").as_double();
        double lon = node.attribute("lon").as_double();
        Node *newNode = new Node(id, lat, lon);
        g.addNode(newNode);
    }
    // add an edge between each node in a way and the next node in the way

    std::unordered_map<std::string, std::unordered_set<std::string>> wayDetails;
    std::unordered_set<std::string> highwayTypes;
    highwayTypes.insert("trunk");
    highwayTypes.insert("primary");
    highwayTypes.insert("secondary");
    highwayTypes.insert("tertiary");
    highwayTypes.insert("residential");
    highwayTypes.insert("unclassified");
    highwayTypes.insert("service");
    highwayTypes.insert("footway");
    highwayTypes.insert("pedestrian");

    for (pugi::xml_node way : osm.children("way"))
    {

        bool valid = true;

        for (pugi::xml_node tag : way.children("tag"))
        {
            std::string key = tag.attribute("k").as_string();
            std::string value = tag.attribute("v").as_string();
            wayDetails[key].insert(value);
            if (key == "highway" && highwayTypes.find(value) != highwayTypes.end())
            {
                valid = true;
                break;
            }
        }
        if (!valid)
        {
            continue;
        }
        pugi::xml_node nd = way.child("nd");
        long prev = nd.attribute("ref").as_llong();
        nd = nd.next_sibling("nd");
        while (nd)
        {
            long curr = nd.attribute("ref").as_llong();
            weightFunction *f = new constantFunction(haversine(g.getNode(prev)->lat, g.getNode(prev)->lon, g.getNode(curr)->lat, g.getNode(curr)->lon));
            g.addEdge(prev, curr, f);
            g.addEdge(curr, prev, f);
            prev = curr;
            nd = nd.next_sibling("nd");
        }
    }

    std::cout << "Way details:\n";
    for (auto it = wayDetails.begin(); it != wayDetails.end(); it++)
    {
        std::cout << "\t" << it->first << " : ";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            std::cout << *it2 << " ";
        }
        std::cout << "\n";
    }

    std::cout << "Number of nodes = " << i << "\n";
    // g.printGraph();
    // g.addEdge(9729981533, 9382382845, new constantFunction(100));
    // g.addEdge(9382382845, 9729981533, new constantFunction(100));
    ShortestPath sp(&g, 33776164);

    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1080;

    SDL_Window *window = NULL;

    SDL_Renderer *renderer = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return 1;
    }
    window = SDL_CreateWindow("Isochrone", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return 1;
    }

    SDL_Texture *backbuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);

    bool quit = false;

    SDL_Event e;

    const double left = -0.137552;
    const double right = 0.0077856;
    const double top = 51.547230;
    const double bottom = 51.447388;

    int mx, my;

    double renderDist = 0;

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        SDL_SetRenderTarget(renderer, backbuffer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        int edgesDrawn = 0;
        for (auto node : sp.getNodes())
        {
            double currDist = (*(sp.distTo(node->getId())))(0);
            if (currDist > renderDist)
            {
                break;
            }
            double c = (currDist / 1000);
            double C = c - std::floor(c);
            int r = C < 0.5 ? 255 : 0;
            int g = C < 0.5 ? 0 : 255;
            SDL_SetRenderDrawColor(renderer, r, g, 0, 255);
            for (auto neighbour : node->getNeighbours())
            {
                // std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
                double startLon = (node->lon - left) * SCREEN_WIDTH / (right - left);
                double startLat = (top - node->lat) * SCREEN_HEIGHT / (top - bottom);
                double endLon = (neighbour.first->lon - left) * SCREEN_WIDTH / (right - left);
                double endLat = (top - neighbour.first->lat) * SCREEN_HEIGHT / (top - bottom);
                double neighbourDist = (*(sp.distTo(neighbour.first->getId())))(0);
                double a = neighbourDist < renderDist ? 1 : (renderDist - currDist) / (neighbourDist - currDist);
                SDL_RenderDrawLine(renderer, (int)startLon, (int)startLat, (int)(startLon + a * (endLon - startLon)), (int)(startLat + a * (endLat - startLat)));
                // std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
                // std::cout << "Render time = " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << "ns\n";
                edgesDrawn++;
            }
        }

        SDL_SetRenderTarget(renderer, NULL);

        SDL_RenderCopy(renderer, backbuffer, NULL, NULL);

        SDL_RenderPresent(renderer);

        std::cout << "Edges drawn = " << edgesDrawn << "\n";
        renderDist = renderDist > 40000 ? 0 : renderDist + 10;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
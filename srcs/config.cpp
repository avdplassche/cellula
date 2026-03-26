#include "config.h"
#include "Types.h"
#include <iostream>

void    fillAppConfig(YAML::Node& file, AppConfig& app) {

    app.window_height = file["window"]["height"].as<float>() - 26;
    app.window_width = file["window"]["width"].as<float>();
    app.window_name = file["window"]["name"].as<std::string>();

    app.playground_margin.x = file["playground"]["margin"][0].as<float>();
    app.playground_margin.y = file["playground"]["margin"][1].as<float>();
    app.playground_size = {app.window_width - app.playground_margin.x * 2,
                            app.window_height - app.playground_margin.y * 2 };
    app.playground_pos = app.playground_margin;
    app.playground_limit = {app.playground_margin.x + app.playground_size.w,
                            app.playground_margin.y + app.playground_size.h};

    app.cell_size = file["cell"]["size"].as<float>();
    app.s_cell_size = {app.cell_size, app.cell_size};

    app.simulation_speed = file["sim"]["speed"].as<float>();
    app.f = file["sim"]["cell_friction"].as<float>();
    app.f_ratio = file["sim"]["friction_ratio"].as<float>();
    app.f_time = file["sim"]["friction_time"].as<float>();

    printConfig(app);
}

void    fillSimConfig(YAML::Node& file, std::vector<SimConfig>& simulations) {
    const YAML::Node& sims = file["simulations"];
    int i = 1;
    for (auto &sim : sims)
    {
        SimConfig conf;

        conf.id = i;
        conf.name = sim["name"].as<std::string>();
        const YAML::Node& types = sim["cell"];
        for (auto& cell : types) {
            if (cell["type"].as<std::string>() == "Predators")
                conf.predator_number = cell["n"].as<int>();
            else if (cell["type"].as<std::string>() == "Prey")
                conf.prey_number = cell["n"].as<int>();
        }
        simulations.push_back(conf);
        i++;
    }
}


void    printConfig(AppConfig& conf) {
    std::cout << "-- PRINT CONFIG --\n\n";
    std::cout << "Window Name : " << conf.window_name << '\n';
    std::cout << "Window Size : [" << conf.window_width << ',' << conf.window_height << "]\n";
    std::cout << "Margin : [" << conf.playground_margin.x << ',' << conf.playground_margin.y << "]\n";
    std::cout << "Playground size : [" << conf.playground_size.w << ',' << conf.playground_size.h << "]\n";
    std::cout << "Playground pos : [" << conf.playground_pos.x << ',' << conf.playground_pos.y << "]\n";
    std::cout << "Cell size : " << conf.cell_size << '\n';
}


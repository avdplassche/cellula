#include "config.h"
#include "Types.h"
#include <iostream>


void    fillConfig(AppConfig& app, YAML::Node& file) {

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

    printConfig(app);
}



void    printConfig(AppConfig& conf) {
    std::cout << "-- PRINT CONFIG --\n\n";
    std::cout << "Window Name : " << conf.window_name << '\n';
    std::cout << "Window Size : [" << conf.window_width << ',' << conf.window_height << "]\n";
    std::cout << "Margin : [" << conf.playground_margin.x << ',' << conf.playground_margin.y << "]\n";
    std::cout << "playground_limit : [" << conf.playground_limit.x << ',' << conf.playground_limit.y << "]\n";
}


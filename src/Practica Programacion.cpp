#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>

struct DataEntry {
    std::time_t date;
    double value;
};

std::vector<DataEntry> parseCSV(const std::string& filename) {
    std::vector<DataEntry> data;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo " << filename << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string dateStr, valueStr;
        if (std::getline(iss, dateStr, ',') && std::getline(iss, valueStr)) {
            std::tm tm = {};
            std::istringstream dateStream(dateStr);
            dateStream >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");

            if (dateStream.fail()) {
                std::cerr << "Error al analizar la fecha en la línea: " << line << std::endl;
                continue;
            }

            double value = std::stod(valueStr);

            std::time_t date = std::mktime(&tm);
            data.push_back({date, value});
        } else {
            std::cerr << "Error al analizar la línea: " << line << std::endl;
        }
    }

    file.close();

    return data;
}

int main() {
    std::string filename;
    std::cout << "Ingrese el nombre del archivo CSV: ";
    std::cin >> filename;

    std::vector<DataEntry> data = parseCSV(filename);

    // Haz algo con los datos, como imprimirlos en la consola
    for (const auto& entry : data) {
        std::cout << "Fecha: " << std::put_time(std::localtime(&entry.date), "%Y-%m-%d %H:%M:%S")
                  << ", Valor: " << entry.value << std::endl;
    }

    return 0;
}

#include "coordinate.hpp"

Coordinate Coordinate::from_xyz_line(std::string &line) {
  std::vector<std::string> items; // e.g. ["H", "0.0", "0.0", "0.0"]
  std::string item;

  for (auto c : line) {
    if (!std::isspace(c)) {
      item += c;
      continue;
    }

    if (item.size() > 0) {
      items.push_back(item);
      item = "";
    }
  }
  items.push_back(item);

  if (items.size() < 4) {
    throw std::runtime_error(
        "Not enough items on xyz line to obtain coordinate");
  }

  auto coordinate = Coordinate();
  coordinate.x = stod(items[1]);
  coordinate.y = stod(items[2]);
  coordinate.z = stod(items[3]);

  return coordinate;
}

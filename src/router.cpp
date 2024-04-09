#include "../include/router.hpp"

void Router::addRoute(http::verb method, const std::string &pathPattern,
                      std::function<void(Context &)> handler) {
  routes.push_back({method, pathPattern, handler});
}

bool Router::route(Context &ctx) {
  const auto &req = ctx.getRequest();
  std::string target = std::string(req.target());

  // Adjust for any potential prefix mismatch or trailing slash
  if (!prefix.empty() && target.find(prefix) == 0) {
    target.erase(0, prefix.size());
  }
  if (!target.empty() && target.back() == '/') {
    target.pop_back();
  }

  for (const auto &routeInfo : routes) {
    if (req.method() != routeInfo.method)
      continue;

    std::vector<std::string> targetSegments = splitPath(target);
    std::vector<std::string> patternSegments = splitPath(routeInfo.pathPattern);

    if (targetSegments.size() != patternSegments.size())
      continue;

    bool match = true;
    for (size_t i = 0; i < patternSegments.size(); ++i) {
      if (patternSegments[i].front() == '{' &&
          patternSegments[i].back() == '}') {
        std::string paramName =
            patternSegments[i].substr(1, patternSegments[i].length() - 2);
        ctx.setParam(paramName, targetSegments[i]);
      } else if (patternSegments[i] != targetSegments[i]) {
        match = false;
        break;
      }
    }

    if (match) {
      routeInfo.handler(ctx);
      return true;
    }
  }
  return false; // No matching route found
}

void Router::setPrefix(const std::string &prefix) {
  this->prefix = prefix;
  // Ensure the prefix is correctly formatted
  if (!this->prefix.empty() && this->prefix.back() != '/') {
    this->prefix += '/';
  }
}

std::vector<std::string> Router::splitPath(const std::string &path) {
  std::vector<std::string> segments;
  size_t start = 0, end = 0;
  while ((end = path.find('/', start)) != std::string::npos) {
    if (end != start) {
      segments.push_back(path.substr(start, end - start));
    }
    start = end + 1;
  }
  if (start < path.size()) {
    segments.push_back(path.substr(start));
  }
  return segments;
}
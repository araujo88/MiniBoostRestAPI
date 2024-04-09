#include "../include/router.hpp"

void Router::addRoute(http::verb method, const std::string &pathPattern,
                      HandlerFunc handler) {
  // Convert dynamic path segments to regex
  std::string regexPattern =
      "^" + prefix +
      std::regex_replace(pathPattern, std::regex("\\{\\w+\\}"), "([^/]+)") +
      "$";
  routes.insert({RouteKey(method, regexPattern), std::move(handler)});
}

bool Router::route(Context &ctx) {
  auto &req = ctx.getRequest();
  std::string target = std::string(req.target());

  for (const auto &[key, handler] : routes) {
    std::smatch match;
    if (req.method() == key.method &&
        std::regex_match(target, match, key.pathRegex)) {
      // Check if we have captured groups (dynamic segments)
      if (match.size() > 1) {
        // Assume the first capture group is the parameter we care about
        // You might need to adjust if your URLs have multiple params
        ctx.setParam("id", match[1].str());
      }
      handler(ctx); // Execute the handler with the context
      return true;
    }
  }
  return false; // No matching route found
}

void Router::setPrefix(const std::string &prefix) { this->prefix = prefix; }

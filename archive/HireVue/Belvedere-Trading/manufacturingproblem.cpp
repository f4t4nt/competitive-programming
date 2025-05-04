#include <bits/stdc++.h>
#include <optional>
using namespace std;

struct Product
{
  std::string Name;
  // std::optional<double> Price;
  double Price;
  std::vector<std::string> Ingredients;
};

std::vector<std::string> SplitString(const std::string& str, const std::string& delimiter)
{
  std::vector<std::string> strs;
  size_t startPos = 0;
  size_t endPos = 0;
  while((endPos = str.find(delimiter, startPos)) != std::string::npos)
  {
    strs.emplace_back(str.substr(startPos, endPos - startPos));
    startPos = endPos + 1;
  }
  strs.emplace_back(str.substr(startPos));
  return strs;
}

std::vector<Product> GetProducts()
{
  std::vector<Product> products{};
  std::string input{};
  while(std::getline(std::cin, input))
  {
    if(input.empty())
    {
      break;
    }
    Product product{};
    auto inputs = SplitString(input, ",");
    if(inputs.size() != 3 && inputs.size() != 4)
    {
      std::cout << "Failed to parse input; Input=\"" << input << "\"" << std::endl;
      throw;
    }
    product.Name = inputs[0];
    if(inputs[1] != "null")
    {
      product.Price = stof(inputs[1]);
    }
    auto numIngredients = stoi(inputs[2]);
    if(numIngredients > 0)
    {
      if(inputs.size() != 4)
      {
        std::cout << "Failed to parse ingredients input; Input=\"" << input << "\"" << std::endl;
        throw;
      }
      product.Ingredients = SplitString(inputs[3], ";");
    }
    products.emplace_back(product);
  }

  return products;
}

double dfs(int u, vector<double> &cost, vector<vector<int>> &children) {
  double rv = -1;
  if (children[u].size() > 0) {
    rv = 0;
    for (auto &v : children[u]) {
      rv += dfs(v, cost, children);
    }
  }
  if (rv == -1 || (cost[u] != -1 && cost[u] < rv)) {
    rv = cost[u];
  }
  return rv;
}

double MySolution(const std::string& target, const std::vector<Product>& products)
{
  map<string, int> mp;
  for (auto &product : products) {
    if (mp.count(product.Name)) continue;
    mp[product.Name] = mp.size();
  }
  // for (auto &e : mp) {
  //   cout << e.first << ' ' << e.second << '\n';
  // }
  int n = mp.size();
  vector<double> cost(n);
  vector<vector<int>> children(n);
  for (auto &product : products) {
    int &id = mp[product.Name];
    // if (product.Price) {
    //   cost[id] = *product.Price;
    // } else {
    //   cost[id] = -1;
    // }
    cost[id] = product.Price;
    for (auto &ingredient : product.Ingredients) {
      children[id].push_back(mp[ingredient]);
    }
  }
  return dfs(mp[target], cost, children);
}

int main()
{
  std::string targetProductName;
  std::getline(std::cin, targetProductName);
  auto products = GetProducts();

  double bestPrice = MySolution(targetProductName, products);
  printf("%.2f\n", bestPrice);
  return 1;
}
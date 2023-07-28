#include <vector>
#include <iostream>
#include <queue>

#define rep(a, b)   for(size_t a = 0; a < (b); ++a)
#define rep1(a, b)  for(size_t a = 1; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define endl        '\n'
#define cd(a)       static_cast<double>(a)
#define csize(a)     static_cast<size_t>(a)

using namespace std;
using ull = size_t;
using Graph = vector<vector<ull>>;
using ll = long long;

struct Employee {
  ll demotivation_level = 0;
  bool motivatable;
};

/**
 * Marks all people motivatable, who are on path, that does not exceed the given threshold.
 * Also, all path segments need to be smaller or equal to the given demotivation level.
 *
 * @param company_hierarchy
 *          Who is the boss of whom. Given as graph, which can be viewed as a tree.
 * @param employees
 *          IDs & Demotivation level of each employee.
 * @param employee
 *          The currently looked at employee.
 * @param path_length
 *          The path length until this employee.
 * @param threshold
 *          The threshold, which the path length is not allowed to exceed.
 */
void markReachable(Graph& company_hierarchy, vector<Employee>& employees,
                     ull employee, ll& path_length, ull& threshold) {
  // If any employee is unreachable, all people under them are not reachable too.
  if (employees.at(employee).demotivation_level + path_length > static_cast<ll>(threshold)) {
    // No need to traverse further down the tree, since elements are implicitly marked as false
    // in the struct.
    return;
  }

  // If the path length is low enough, the person is still motivatable.
  employees.at(employee).motivatable = true;
  for (const auto& underling : company_hierarchy.at(employee)) {
    auto l = path_length + employees[employee].demotivation_level;
    markReachable(company_hierarchy, employees, underling, l, threshold);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.precision(10);

  ull no_employees, motivational_level;
  cin >> no_employees >> motivational_level;

  // Information on each individual employee.
  auto employees = vector<Employee>(no_employees+1);
  // The top-down hierarchy.
  auto company_hierarchy = Graph(no_employees+1);
  // The bottom up hierarchy
  auto bosses = vector<ull>(no_employees+1);

  rep(i, no_employees) {
    ll level;
    cin >> level;

    employees[i+1] = Employee{level, false};
  }

  /*
   * -----------------------------------------------------------
   *    Find all elements, that are reachable with threshold
   * -----------------------------------------------------------
   */

  rep1(i, no_employees) {
    ull boss;
    cin >> boss;

    company_hierarchy[boss].push_back(i+1);
    bosses[i+1] = boss;
  }

  auto start = ll{0};
  markReachable(company_hierarchy, employees, 1, start, motivational_level);

  /*
   * -----------------------------------------------------------
   *        Apply DP on tree in bottom up fashion
   * -----------------------------------------------------------
   */

  auto unreachable_nodes = ull(0);

  auto q = queue<ull>();
  auto dp = vector<ull>(no_employees + 1, 0);

  // Processed children per node
  auto status = vector<ull>(no_employees + 1, 0);
  auto no_children = vector<ull>(no_employees + 1, 0);

  // Leafs of tree as starting points
  // Also memorize unreachable candidate to get them fired.
  auto leafs = vector<ull>();
  rep1(i, company_hierarchy.size()) {
    if (employees[i].motivatable) {
      no_children[bosses[i]]++;
      if (company_hierarchy[i].size() == 0)
        q.push(i);
    } else {
      unreachable_nodes++;
    }
  }

  // no_children is required to find the leafs, since a node can have only unmotivatable
  // children, which turns it from being an inner node to being a leaf.
  rep1(i, company_hierarchy.size()) {
    if (employees[i].motivatable && no_children[i] == 0) {
      q.push(i);
    }
  }

  while (!q.empty()) {
    auto f = q.front();
    q.pop();

    // First process all children of a node.
    if (status[f] < no_children[f]) {
      q.push(f);
      continue;
    }

    if (no_children[f] == 0) {
      dp[f] = 1;
    } else {
      auto sum = 0;
      for (const auto& underling : company_hierarchy[f]) {
        if (employees[underling].motivatable) {
          sum += dp[underling];
        }
      }
      sum--;

      if (sum == 0) sum = 1;
      dp[f] = sum;
    }

    const auto boss = bosses[f];
    status[boss]++;
    if (status[boss] == no_children[boss]) {
      q.push(boss);
    }
  }

  cout << dp[1] << " " << unreachable_nodes << endl;

  return 0;
}
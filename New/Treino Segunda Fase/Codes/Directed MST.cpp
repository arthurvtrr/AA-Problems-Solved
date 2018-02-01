#include <bits/stdc++.h>

using namespace std;

private List<Node> cycle;

public AdjacencyList getMinBranching(Node root, AdjacencyList list) {
    AdjacencyList reverse = list.getReversedList();
    // remove all edges entering the root
    if (reverse.getAdjacent(root) != null) {
        reverse.getAdjacent(root).clear();
    }
    AdjacencyList outEdges = new AdjacencyList();
    // for each node, select the edge entering it with smallest weight
    for (Node n : reverse.getSourceNodeSet()) {
        List<Edge> inEdges = reverse.getAdjacent(n);
        if (inEdges.isEmpty()) {
            continue;
        }
        Edge min = inEdges.get(0);
        for (Edge e : inEdges) {
            if (e.getWeight() < min.getWeight()) {
                min = e;
            }
        }
        outEdges.addEdge(min.getTo(), min.getFrom(), min.getBond());
    }

    // detect cycles
    List<List<Node>> cycles = new ArrayList<List<Node>>();
    cycle = new ArrayList<Node>();
    getCycle(root, outEdges);
    cycles.add(cycle);
    for (Node n : outEdges.getSourceNodeSet()) {
        if (!n.isVisited()) {
            cycle = new ArrayList<Node>();
            getCycle(n, outEdges);
            cycles.add(cycle);
        }
    }

    // for each cycle formed, modify the path to merge it into another part of the graph
    AdjacencyList outEdgesReverse = outEdges.getReversedList();

    for (List<Node> x : cycles) {
        if (x.contains(root)) {
            continue;
        }
        mergeCycles(x, list, reverse, outEdges, outEdgesReverse);
    }
    return outEdges;
}

private void mergeCycles(List<Node> cycle, AdjacencyList list, AdjacencyList reverse, AdjacencyList outEdges, AdjacencyList outEdgesReverse) {
    List<Edge> cycleAllInEdges = new ArrayList<Edge>();
    Edge minInternalEdge = null;
    // find the minimum internal edge weight
    for (Node n : cycle) {
        for (Edge e : reverse.getAdjacent(n)) {
            if (cycle.contains(e.getTo())) {
                if (minInternalEdge == null || minInternalEdge.getWeight() > e.getWeight()) {
                    minInternalEdge = e;
                    continue;
                }
            } else {
                cycleAllInEdges.add(e);
            }
        }
    }
    // find the incoming edge with minimum modified cost
    Edge minExternalEdge = null;
    int minModifiedWeight = 0;
    for (Edge e : cycleAllInEdges) {
        int w = e.getWeight() - (outEdgesReverse.getAdjacent(e.getFrom()).get(0).getWeight() - minInternalEdge.getWeight());
        if (minExternalEdge == null || minModifiedWeight > w) {
            minExternalEdge = e;
            minModifiedWeight = w;
        }
    }
    // add the incoming edge and remove the inner-circuit incoming edge
    Edge removing = outEdgesReverse.getAdjacent(minExternalEdge.getFrom()).get(0);
    outEdgesReverse.getAdjacent(minExternalEdge.getFrom()).clear();
    outEdgesReverse.addEdge(minExternalEdge.getTo(), minExternalEdge.getFrom(), minExternalEdge.getBond());
    List<Edge> adj = outEdges.getAdjacent(removing.getTo());
    for (Iterator<Edge> i = adj.iterator(); i.hasNext();) {
        if (i.next().getTo() == removing.getFrom()) {
            i.remove();
            break;
        }
    }
    outEdges.addEdge(minExternalEdge.getTo(), minExternalEdge.getFrom(), minExternalEdge.getBond());
}

private void getCycle(Node n, AdjacencyList outEdges) {
    n.setVisited(true);
    cycle.add(n);
    if (outEdges.getAdjacent(n) == null) {
        return;
    }
    for (Edge e : outEdges.getAdjacent(n)) {
        if (!e.getTo().isVisited()) {
            getCycle(e.getTo(), outEdges);
        }
    }
}

int main() {

    return 0;
}

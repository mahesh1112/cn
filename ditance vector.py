import copy
def create_network():
    network = {}
    num_nodes = int(input("Enter the number of nodes: "))
    flag = True

    # Initialize the network with empty distances for each node
    for i in range(num_nodes):
        node = input(f"Enter the name of node {i + 1}: ")
        network[node] = {}
    
    # Populate the distances for each node
    for i in network.keys():
        distances = {}
        for j in network.keys():
            if i != j:
                distance = input(f"Enter the distance from {i} to node {j} (Enter 'inf' if not connected): ")
                distances[j] = float('inf') if distance.lower() == 'inf' else int(distance)
                
                if distance.lower() != "inf" and int(distance) < 0:
                    flag = False
            else:
                distances[i] = 0
        network[i] = distances
                

    return network, flag


def distance_vector(network, nodes):
    updated = True
    while updated:
        updated = False
        temp_network = copy.deepcopy(network)
        for k in nodes:
            for i in nodes:
                for j in nodes:
                    temp_network[i][j] = min(temp_network[i][j], temp_network[i][k] + temp_network[k][j])
                    if temp_network[i][j] != network[i][j]:
                        updated = True
        network = copy.deepcopy(temp_network)
    return network

def print_routing_tables(network, nodes):
    for node in nodes:
        print(f"Routing table for {node}:")
        for dest, dist in network[node].items():
            print(f" -> To {dest}: Distance {dist}")
        print()

network, flag = create_network()
print(network)

if flag:
    nodes = list(network.keys())
    updated_network = distance_vector(network, nodes)
    print_routing_tables(updated_network, nodes)
else:
    print("Contains Negative cycle")

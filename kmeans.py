import sys

assert (2 <= len(sys.argv) <= 3)
assert (sys.argv[1]).isnumeric()
assert (int(sys.argv[1]) > 0)

if len(sys.argv) == 3:
    assert (sys.argv[-1]).isnumeric()
    assert (int(sys.argv[-1]) > 0)
    iterations = sys.argv[-1]

k = int(sys.argv[1])
iterations = 200


def points_array():
    points = []
    while True:
        point = []
        try:
            for val in input().strip('\n').split(','):
                point.append(float(val))
        except EOFError:
            break
        if point:
            points.append(tuple(point))
    return points


def get_dimension(points):
    return len(points[0])


points = points_array()
dimension = get_dimension(points)
centroids = points[:k]
point_cluster_dict = dict()


def distance(point, kmean):
    distance = 0
    for dim in range(dimension):
        distance += (point[dim] - kmean[dim]) * (point[dim] - kmean[dim])
    return distance ** 0.5


def find_cluster_dist(point):
    cluster_index = 0
    for i in range(k):
        if distance(point, centroids[i]) < distance(point, centroids[cluster_index]):
            cluster_index = i
    point_cluster_dict[point] = cluster_index


def reverse_dict():
    cluster_points_dict = dict()
    for point in points:
        cluster = point_cluster_dict[point]
        try:
            cluster_points_dict[cluster].append(point)
        except KeyError:
            cluster_points_dict[cluster] = [point]
    return cluster_points_dict


def bool_centroids_changed(cluster_points_dict):
    is_changed = False
    for i in range(k):
        new_centroid = cluster_mean(cluster_points_dict[i])
        if centroids[i] != new_centroid:
            is_changed = True
            centroids[i] = new_centroid
    return is_changed


def cluster_mean(cluster):
    mean = []
    for dim in range(dimension):
        value = 0
        for point in cluster:
            value += point[dim]
        mean.append((value / len(cluster)))
    return mean


def kmeans_clustering():
    for i in range(len(points)):
        point_cluster_dict[points[i]] = -1
    curr_iter = 0
    changed = True
    while curr_iter < iterations and changed:
        for point in points:
            find_cluster_dist(point)
        changed = bool_centroids_changed(reverse_dict())
        curr_iter += 1


kmeans_clustering()

for i in range(k):
    for j in range(dimension):
        centroids[i][j] = '{0:.4f}'.format(centroids[i][j])
for centroid in centroids:
    print(','.join(centroid))

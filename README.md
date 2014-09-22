clustering-spoj-users
=====================

A tool that retrieves the information of SPOJ users and clusters them using their pairwise Jaccard Coefficients

Pre-requisites: Python2.7, GNU G++ compiler and Gephi for graph visualization.

Running the script fetch_and_cluster.sh will guide you through the whole process.

The use of the individual files are as follows:
getuserdata.py - Fetches the usernames and lists of solved problems and stores them in the file userdata.dat
parseuserdata.py - Parses the file userdata.dat and converts the data into a format which can be easily read by the C++ clustering program (saved in the file parsed_data.dat)
clusterdata.cpp - Clusters the data and stores the results in clustered_data.dat
gmlconverter.py - Converts the data into GML format for visualization in Gephi and stores it in plot_graph.gml

Clustering is done by first forming a Maximum Spanning Tree out of the data set using Jaccard Similarity Coefficient between users as the edge weights and then breaking the least similar links one-by-one until the required no. of clusters is obtained.

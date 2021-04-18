/**
	simulate.cpp

	Purpose: implements a Simulation class which
	simulates a robot living in a 2D world. Relies 
	on localization code from localizer.py 

	This file is incomplete! Your job is to make 
	this code work. 
*/

#include <algorithm>
#include "simulate.h"
#include "localizer.cpp"

/**
Constructor for the Simulation class.
*/
Simulation::Simulation(vector < vector <char> > map, 
	float blurring,
	float hit_prob, 
	std::vector<int> start_pos
	) 
{
	grid = map;
	blur = blurring;
	p_hit = hit_prob;
	p_miss = 1 - p_hit;
	beliefs = initialize_beliefs(map);
	incorrect_sense_prob = p_miss / (p_hit + p_miss);
	true_pose = start_pos;
	prev_pose = true_pose;
}

/**
Grabs colors from the grid map.
*/
vector <char> Simulation::get_colors() {
	vector <char> all_colors;
	char color;
	int i,j;
	for (i=0; i<height; i++) {
		for (j=0; j<width; j++) {
			color = grid[i][j];
			if(std::find(all_colors.begin(), all_colors.end(), color) != all_colors.end()) {
				/* v contains x */
			} else {
				all_colors.push_back(color);
				cout << "adding color " << color << endl;
				/* v does not contain x */
			}
		}
	}
	colors = all_colors;
	num_colors = colors.size();
	return colors;
}

/**
You can test your code by running this function. 

Do that by first compiling this file and then 
running the output.
*/

int main() {
	
 	vector < vector <char> > map;
 	vector <char> mapRow;
 	int i, j, randInt;
  	int dx = 1;
  	int dy = 1;
 	char color;
 	std::vector<int> pose(2);
	//std::vector<vector<float>> beliefs = zeros(
 	for (i = 0; i < 4; i++)
 	{
 		mapRow.clear();
 		for (j=0; j< 4; j++)
 		{
 			randInt = rand() % 2;
 			if (randInt == 0 ) {
 				color = 'r';
 			} 
 			else {
 				color = 'g';
 			}
 			mapRow.push_back(color);
 		}
 		map.push_back(mapRow);
 	}
 	cout << "map is\n";
 	Simulation simulation (map, 0.1, 0.9, pose);
 	cout << "initialization success!\n";
 	show_grid(map);
  	
 	
  	
  	for(unsigned int i = 0; i<6; i++){
      cout<<"========================================"<<endl;
      cout << "x, y = (" << simulation.true_pose[0] << ", " << simulation.true_pose[1] << ") | Current belief:" << endl;
      show_grid(simulation.beliefs);      
      char meas = map[simulation.true_pose[0]][simulation.true_pose[1]];
      cout<<"Measurement: "<<meas<<endl;
      simulation.beliefs = sense(meas, map, simulation.beliefs, simulation.p_hit, simulation.p_miss);
      cout<<"Updated beliefs:"<<endl;
      show_grid(simulation.beliefs);
      cout<<"Moving dx = "<<dx<<" | dy = "<<dy<<endl;
      simulation.beliefs = move(dy, dx, simulation.beliefs, simulation.blur);
      //show_grid(simulation.beliefs);
      simulation.true_pose[0] = simulation.true_pose[0] + dx;
      simulation.true_pose[1] = simulation.true_pose[1] + dy;
      if(simulation.true_pose[0] >= simulation.beliefs.size()) { simulation.true_pose[0] = simulation.true_pose[0] - simulation.beliefs.size(); }
      if(simulation.true_pose[1] >= simulation.beliefs[0].size()) { simulation.true_pose[1] = simulation.true_pose[1] - simulation.beliefs[0].size(); }
 	}
 	return 0;
 }

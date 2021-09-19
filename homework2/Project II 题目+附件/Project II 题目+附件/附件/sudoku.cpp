#include<iostream>
#include<chrono>
int ans = 0;
int main(){
	/* read file */
	
	/* start */ 
	std::chrono::time_point<std::chrono::system_clock> server_create_time_ = std::chrono::system_clock::now();
	
	/* solve problem */
	
	/* end */
	std::cout<<"solution_count = "<<ans<<std::endl;
	auto current_time = std::chrono::system_clock::now();
	std::chrono::duration<double, std::milli> duration_mili = current_time - server_create_time_;
	std::cout<<"PrintDuration : duration_mili duration = "<< (long)duration_mili.count()<<" ms";
}

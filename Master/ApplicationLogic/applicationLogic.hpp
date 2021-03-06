#ifndef __APPLICATIONLOGIC_HPP
#define __APPLICATIONLOGIC_HPP

#include "hwlib.hpp"
#include <math.h>

template< typename T, int N >
class lookup{
private:
	std::array<T, N> values = {};
public:
	template< typename F >
	constexpr lookup(F function){
		for (int i=0; i < N; i+=6){
			values[i] = function(i);
		}
	}
	constexpr T get(int n) const{
		return values[n];
	}
};

constexpr double pow(double g, int n){
	double result = 1;
	while(n > 0){
		result *= g;
		--n;
	}
	return result;
}

constexpr double fac(int n){
	double result = 1;
	while(n > 0){
		result *= n;
		--n;
	}
	return result;
}

constexpr double radians_from_degrees(int degrees){
	return 2 * 3.14 * (degrees / 360.0);
}

constexpr double scaled_sine_from_degrees(int degrees){
	return 9* sin(radians_from_degrees(degrees));                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
}

constexpr double scaled_cosine_from_degrees(int degrees){
	return 9* cos(radians_from_degrees(degrees));
}

static void swap(uint8_t *xp, uint8_t *yp){  
	uint8_t temp = *xp;  
	*xp = *yp;  
	*yp = temp;  
}  

static void bubbleSort(std::array<uint8_t, 32> & scores, std::array<uint8_t, 32> & numbers, int n){  
    int i, j;  
    for (i = 0; i < n-1; i++){
        for (j = 0; j < n-i-1; j++){  
            if (scores[j] > scores[j+1]) {
                swap(&scores[j+1], &scores[j]);
                swap(&numbers[j+1], &numbers[j]);
            }  
        }      
    }
}

#endif /*applicationLogic.hpp*/
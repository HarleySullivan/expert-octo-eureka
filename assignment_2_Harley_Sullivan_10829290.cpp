// Assignment 2 

// Program to read in course data and return the mean, standard deviation and standard error on mean for 
// user selected courses. The code assumes the data file is saved in the same folder as the code so this must
// be the case.
// Author: Harley Sullivan
// Date:   23/02/2024

#if __cplusplus >= 201703L
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

struct course_data 
{
  double mark;
  int course_code;
  std::string title;
};

// Function to calculate the mean mark for selected courses
double calculate_mean_mark(const std::vector<course_data>& courses) 
{
  double sum = 0.0;
  for (const auto& course : courses) 
  {
    sum += course.mark;
  }

  std::cout << "Sum of marks: " << sum << std::endl;
  std::cout << "Number of courses: " << courses.size() << std::endl;

  if (!courses.empty()) 
  {
    return sum / courses.size();
  } 
  else 
  {
    return 0.0; // Handle the case where the vector is empty to avoid division by zero
  }
}

// Function to caculated standard deviation for selected courses
double calculate_standard_deviation(const std::vector<course_data>& courses) 
{
  double sum = 0.0;
  double sum_squared_diff = 0.0;

  for (const auto& course : courses) 
  {
    sum += course.mark;
    sum_squared_diff += std::pow(course.mark, 2);
  }

    

  if (!courses.empty()) 
  {
    double mean = sum / courses.size();
    double mean_squared = std::pow(mean, 2);
    double variance = (sum_squared_diff / courses.size()) - mean_squared;
    double standard_deviation = std::sqrt(variance);

    return standard_deviation;
  } 
  else 
  {
    std::cerr << "Error: Empty vector. Unable to calculate standard deviation." << std::endl;
    return 0.0; // Handle the case where the vector is empty to avoid division by zero
  }
}

// Function to caculate atandard error on mean for selected courses
double calculate_standard_error(const std::vector<course_data>& courses, double standard_deviation) 
{
  if (!courses.empty())
  {
    double standard_error = standard_deviation / std::sqrt(courses.size());

    return standard_error;
    } 
  else 
  {
    std::cerr << "Error: Empty vector. Unable to calculate standard error." << std::endl;
    return 0.0; // Handle the case where the vector is empty to avoid division by zero
  }
}

int main() 
{
  // Get the code file path
  std::string code_file_path = __FILE__;

  // Extract the directory path from the code file path
  size_t last_slash = code_file_path.find_last_of("/\\");
  std::string directory_path = code_file_path.substr(0, last_slash + 1);

  // Ask the user for the filename
  std::cout << "Enter the filename to read: ";
  std::string filename;
  std::getline(std::cin, filename);

  // Combine the directory path with the filename
  std::string full_path = directory_path + filename;

  // Open the file
  std::ifstream input_file(full_path);

  // Check if the file is successfully opened
  if (!input_file.is_open()) 
  {
    std::cerr << "Error opening the file!" << std::endl;
    return 1; // Exit the program with an error code
  }

  double mark;
  int course_code;
  std::string title;

  std::string line;

  // Count of data points
  int data_point_count = 0;

  // Vector to store course data
  std::vector<course_data> course_data_vector;

  // Read data from the file and store it in the vector
  while (std::getline(input_file, line)) 
  {
    // Use a string stream to parse the line
    std::istringstream iss(line);

    // Read data from the string stream
    course_data course_data;

    if (iss >> course_data.mark >> course_data.course_code) 
    {
      // Capture the entire course title
      std::getline(iss, course_data.title);

      // Store the data in the vector
      course_data_vector.push_back(course_data);

      // Increment the data point count
      data_point_count++;
    } 
    else 
    {
      std::cerr << "Error parsing line: " << line << std::endl;
    }
  }

  // Close the file
  input_file.close();

  // Print the number of data points
  std::cout << "Number of data points: " << data_point_count << std::endl;

  char selection;
  std::cout<<"If you would like to look at all courses input A, if you would like to look at a particular year input the year (1,2,3,4): "<<std::endl;
  while (!(std::cin>>selection)||(selection != 'A' && selection != '1' && selection != '2' && selection != '3' && selection != '4'))
  {
    std::cin.clear();  
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
    std::cout<<"Invalid input. Please type 'A' for all courses or 'B' for a particular year: ";
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    

  char order;
  std::cout<<"If you would like to order the courses by title input A, if you would like the courses to be ordered by course code input B: "<<std::endl;
  while (!(std::cin>>order)||(order != 'A' && order != 'B'))
  {
    std::cin.clear();  
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
    std::cout<<"Invalid input. Please type 'A' to order by title or 'B' to order by course code: ";
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  // Print the content of the vector using iterators
  if (selection == 'A' && order == 'B')
  {
    std::cout << "All courses ordered by course code:" << std::endl;
    for (auto it = course_data_vector.begin(); it != course_data_vector.end(); ++it) 
    {
    std::cout << "PHYS " << it->course_code << it->title << std::endl;
    }
    // Calculate and print the mean mark
    double mean_mark = calculate_mean_mark(course_data_vector);
    std::cout << "Mean Mark for selected courses: " << mean_mark << std::endl;

    // Calculate and print standard deviation
    double standard_deviation = calculate_standard_deviation(course_data_vector);
    std::cout << "Standard deviation for selected courses: " << standard_deviation << std::endl;

    //calculate and print standard error on mean
    double standard_error = calculate_standard_error(course_data_vector, standard_deviation);
    std::cout << "Standard error on mean for selected courses: " << standard_error << std::endl;

  }

  if (selection == 'A' && order == 'A')
  {
    // Sort the vector alphabetically based on the title
    std::sort(course_data_vector.begin(), course_data_vector.end(),
    [](const auto& a, const auto& b) 
    {
      return a.title < b.title; // Comparison based on the title 
    });

    // Print the sorted content of the vector
    std::cout << "All courses ordered alphabetically by title:" << std::endl;
    for (const auto& course_data_vector : course_data_vector) 
    {
      std::cout << "PHYS " << course_data_vector.course_code << course_data_vector.title << std::endl;
    }
    // Calculate and print the mean mark
    double mean_mark = calculate_mean_mark(course_data_vector);
    std::cout << "Mean Mark for selected courses: " << mean_mark << std::endl;

    // Calculate and print standard deviation
    double standard_deviation = calculate_standard_deviation(course_data_vector);
    std::cout << "Standard deviation for selected courses: " << standard_deviation << std::endl;

    // Calculate and print standard error on mean
    double standard_error = calculate_standard_error(course_data_vector, standard_deviation);
    std::cout << "Standard error on mean for selected courses: " << standard_error << std::endl;

  }

  if (selection == '1' && order == 'A')
  {
    // Sort the vector alphabetically based on the title
    std::sort(course_data_vector.begin(), course_data_vector.end(),
    [](const auto& a, const auto& b) 
    {
    return a.title < b.title; // Comparison based on the title 
    });

    // Print the sorted content of the vector
    std::cout << "Courses for year 1 ordered alphabetically: "<< std::endl;
    std::vector<course_data> year_1_courses;

    for (const auto& course_data_vector : course_data_vector) 
    {
      // Extract the first digit of the course code
        
      int first_digit = course_data_vector.course_code / 10000; 
      
      if (first_digit == 1) 
      {
        std::cout << "PHYS " << course_data_vector.course_code << " " << course_data_vector.title << std::endl;
        year_1_courses.push_back(course_data_vector);
      }
    }
    double mean_mark = calculate_mean_mark(year_1_courses);
    std::cout << "Mean Mark for year 1 courses: " << mean_mark << std::endl;

    // Calculate and print standard deviation
    double standard_deviation = calculate_standard_deviation(year_1_courses);
    std::cout << "Standard deviation for selected courses: " << standard_deviation << std::endl;

    // Calculate and print standard error on mean
    double standard_error = calculate_standard_error(year_1_courses, standard_deviation);
    std::cout << "Standard error on mean for selected courses: " << standard_error << std::endl;

  }

  if (selection == '1' && order == 'B')
  {
    
    // Print the sorted content of the vector
    std::cout << "Courses for year 1 ordered by course code: "<< std::endl;
    std::vector<course_data> year_1_courses;

    for (const auto& course_data_vector : course_data_vector) 
    {
      // Extract the first digit of the course code
        
      int first_digit = course_data_vector.course_code / 10000; 

      if (first_digit == 1) 
      {
        std::cout << "PHYS " << course_data_vector.course_code << " " << course_data_vector.title << std::endl;
        year_1_courses.push_back(course_data_vector);
      }
    }
    double mean_mark = calculate_mean_mark(year_1_courses);
    std::cout << "Mean Mark for year 1 courses: " << mean_mark << std::endl;

    // Calculate and print standard deviation
    double standard_deviation = calculate_standard_deviation(year_1_courses);
    std::cout << "Standard deviation for selected courses: " << standard_deviation << std::endl;

    // Calculate and print standard error on mean
    double standard_error = calculate_standard_error(year_1_courses, standard_deviation);
    std::cout << "Standard error on mean for selected courses: " << standard_error << std::endl;

  }

  if (selection == '2' && order == 'A')
  {
    // Sort the vector alphabetically based on the title
    std::sort(course_data_vector.begin(), course_data_vector.end(),
    [](const auto& a, const auto& b) 
    {
    return a.title < b.title; // Comparison based on the title
    });

    // Print the sorted content of the vector
    std::cout << "Courses for year 2 ordered alphabetically: "<< std::endl;
    std::vector<course_data> year_2_courses;

    for (const auto& course_data_vector : course_data_vector) 
    {
      // Extract the first digit of the course code
        
      int first_digit = course_data_vector.course_code / 10000; 

      if (first_digit == 2) 
      {
        std::cout << "PHYS " << course_data_vector.course_code << " " << course_data_vector.title << std::endl;
        year_2_courses.push_back(course_data_vector);
      }
    }
    double mean_mark = calculate_mean_mark(year_2_courses);
    std::cout << "Mean Mark for year 2 courses: " << mean_mark << std::endl;

    // Calculate and print standard deviation
    double standard_deviation = calculate_standard_deviation(year_2_courses);
    std::cout << "Standard deviation for selected courses: " << standard_deviation << std::endl;


    // Calculate and print standard error on mean
    double standard_error = calculate_standard_error(year_2_courses, standard_deviation);
    std::cout << "Standard error on mean for selected courses: " << standard_error << std::endl;

  }

  if (selection == '2' && order == 'B')
  {
    
    // Print the sorted content of the vector
    std::cout << "Courses for year 2 ordered by course code: "<< std::endl;
    std::vector<course_data> year_2_courses;

    for (const auto& course_data_vector : course_data_vector) 
    {
      // Extract the first digit of the course code
        
      int first_digit = course_data_vector.course_code / 10000; 

      if (first_digit == 2) 
      {
        std::cout << "PHYS " << course_data_vector.course_code << " " << course_data_vector.title << std::endl;
        year_2_courses.push_back(course_data_vector);
      }
    }
    double mean_mark = calculate_mean_mark(year_2_courses);
    std::cout << "Mean Mark for year 2 courses: " << mean_mark << std::endl;

    // Calculate and print standard deviation
    double standard_deviation = calculate_standard_deviation(year_2_courses);
    std::cout << "Standard deviation for selected courses: " << standard_deviation << std::endl;

    // Calculate and print standard error on mean
    double standard_error = calculate_standard_error(year_2_courses, standard_deviation);
    std::cout << "Standard error on mean for selected courses: " << standard_error << std::endl;

  }

  if (selection == '3' && order == 'A')
  {
    // Sort the vector alphabetically based on the title
    std::sort(course_data_vector.begin(), course_data_vector.end(),
    [](const auto& a, const auto& b) 
    {
    return a.title < b.title; // Comparison based on the title
    });

    // Print the sorted content of the vector
    std::cout << "Courses for year 3 ordered alphabetically: "<< std::endl;
    std::vector<course_data> year_3_courses;

    for (const auto& course_data_vector : course_data_vector) 
    {
      // Extract the first digit of the course code
        
      int first_digit = course_data_vector.course_code / 10000;

      if (first_digit == 3) 
      {
        std::cout << "PHYS " << course_data_vector.course_code << " " << course_data_vector.title << std::endl;
        year_3_courses.push_back(course_data_vector);
      }
    }
    double mean_mark = calculate_mean_mark(year_3_courses);
    std::cout << "Mean Mark for year 3 courses: " << mean_mark << std::endl;

    // Calculate and print standard deviation
    double standard_deviation = calculate_standard_deviation(year_3_courses);
    std::cout << "Standard deviation for selected courses: " << standard_deviation << std::endl;

    // Calculate and print standard error on mean
    double standard_error = calculate_standard_error(year_3_courses, standard_deviation);
    std::cout << "Standard error on mean for selected courses: " << standard_error << std::endl;

  }

  if (selection == '3' && order == 'B')
  {
    
    // Print the sorted content of the vector
    std::cout << "Courses for year 3 ordered by course code: "<< std::endl;
    std::vector<course_data> year_3_courses;

    for (const auto& course_data_vector : course_data_vector) 
    {
      // Extract the first digit of the course code
        
      int first_digit = course_data_vector.course_code / 10000; 

      if (first_digit == 3) 
      {
        std::cout << "PHYS " << course_data_vector.course_code << " " << course_data_vector.title << std::endl;
        year_3_courses.push_back(course_data_vector);
      }
    }
    double mean_mark = calculate_mean_mark(year_3_courses);
    std::cout << "Mean Mark for year 3 courses: " << mean_mark << std::endl;

    // Calculate and print standard deviation
    double standard_deviation = calculate_standard_deviation(year_3_courses);
    std::cout << "Standard deviation for selected courses: " << standard_deviation << std::endl;

    // Calculate and print standard error on mean
    double standard_error = calculate_standard_error(year_3_courses, standard_deviation);
    std::cout << "Standard error on mean for selected courses: " << standard_error << std::endl;

  }

  if (selection == '4' && order == 'A')
  {
    // Sort the vector alphabetically based on the title
    std::sort(course_data_vector.begin(), course_data_vector.end(),
    [](const auto& a, const auto& b) 
    {
    return a.title < b.title; // Comparison based on the title
    });

    // Print the sorted content of the vector
    std::cout << "Courses for year 4 ordered alphabetically: "<< std::endl;
    std::vector<course_data> year_4_courses;

    for (const auto& course_data_vector : course_data_vector) 
    {
      // Extract the first digit of the course code
        
      int first_digit = course_data_vector.course_code / 10000; 

      if (first_digit == 4) 
      {
        std::cout << "PHYS " << course_data_vector.course_code << " " << course_data_vector.title << std::endl;
        year_4_courses.push_back(course_data_vector);
      }
    }
    double mean_mark = calculate_mean_mark(year_4_courses);
    std::cout << "Mean Mark for year 4 courses: " << mean_mark << std::endl;

    // Calculate and print standard deviation
    double standard_deviation = calculate_standard_deviation(year_4_courses);
    std::cout << "Standard deviation for selected courses: " << standard_deviation << std::endl;

    // Calculate and print standard error on mean
    double standard_error = calculate_standard_error(year_4_courses, standard_deviation);
    std::cout << "Standard error on mean for selected courses: " << standard_error << std::endl;

  }

  if (selection == '4' && order == 'B')
  {
    
    // Print the sorted content of the vector
    std::cout << "Courses for year 4 ordered by course code: "<< std::endl;
    std::vector<course_data> year_4_courses;

    for (const auto& course_data_vector : course_data_vector) 
    {
      // Extract the first digit of the course code
        
      int first_digit = course_data_vector.course_code / 10000; 

      if (first_digit == 4) 
      {
        std::cout << "PHYS " << course_data_vector.course_code << " " << course_data_vector.title << std::endl;
        year_4_courses.push_back(course_data_vector);
      }
    }
    double mean_mark = calculate_mean_mark(year_4_courses);
    std::cout << "Mean Mark for year 4 courses: " << mean_mark << std::endl;

    // Calculate and print standard deviation
    double standard_deviation = calculate_standard_deviation(year_4_courses);
    std::cout << "Standard deviation for selected courses: " << standard_deviation << std::endl;

    // Calculate and print standard error on mean
    double standard_error = calculate_standard_error(year_4_courses, standard_deviation);
    std::cout << "Standard error on mean for selected courses: " << standard_error << std::endl;

  }
    

  return 0; // Exit the program 
}

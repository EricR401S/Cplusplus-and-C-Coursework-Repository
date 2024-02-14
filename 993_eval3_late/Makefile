all: cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4

cyoa-step1: generate_story.cpp step1.cpp my_story_class.hpp
	g++ -o cyoa-step1 -std=gnu++98 -Wall -Werror -ggdb3 generate_story.cpp step1.cpp

cyoa-step2: generate_story.cpp step2.cpp my_story_class.hpp
	g++ -o cyoa-step2 -std=gnu++98 -Wall -Werror -ggdb3 generate_story.cpp step2.cpp

cyoa-step3: generate_story.cpp step3.cpp my_story_class.hpp
	g++ -o cyoa-step3 -std=gnu++98 -Wall -Werror -ggdb3 generate_story.cpp step3.cpp

cyoa-step4: generate_story.cpp step4.cpp my_story_class.hpp
	g++ -o cyoa-step4 -std=gnu++98 -Wall -Werror -ggdb3 generate_story.cpp step4.cpp

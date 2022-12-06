GPP=g++
# FLAGS=-Wall -Werror -Wextra
task=task_4

all: clean task

task:
	$(GPP) $(FLAGS) $(task).cpp -o $(task)
	./$(task)

clean:
	rm -rf $(task)

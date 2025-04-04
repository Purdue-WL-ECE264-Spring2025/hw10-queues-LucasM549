#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {
	//printf("%p", &(q->data));
	//printf("test2");
	
	insert_at_tail(&(q->data), serialize(state));
	return;
}

struct game_state dequeue(struct queue *q) { 
	
	return deserialize(remove_from_head(&(q->data)));
}

struct game_state copyGame(struct game_state game)
{	
	struct game_state newGame;

	//printf("test(1)\n");
	
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			newGame.tiles[i][j] = game.tiles[i][j];
		}
	}

	newGame.empty_row = game.empty_row;
	newGame.empty_col = game.empty_col;
	newGame.num_steps = game.num_steps;

	return newGame;
}

int searchList(struct linked_list list, size_t value)
{
	struct list_node * testNode;
	
	if(list.head == NULL)
	{
		return 0;
	}
	
	testNode = list.head;

	do
	{
		if(testNode->value == value)
		{
			return 1;
		}
		testNode = testNode->next;
	}
	while(testNode != NULL);

	return 0;
}

int number_of_moves(struct game_state start) {

	//return  -1;
//struct queue q;
	struct linked_list l;

	struct linked_list tracker;

	//return 3;

	l.head = NULL;
	tracker.head = NULL;
	
	insert_at_tail(&l, serialize(start));

	//q.data = l;

	//printf("%p", q.data)

	struct game_state game;
	struct game_state newGame;	

	int col = 0;
	int row = 0;
	int flag = 0;
	size_t serial;

	do
	{
		/*	
		int k = 0;
		
		printf("[ ");
  	for (struct list_node *cur = l.head; cur != NULL; cur = cur->next) {
    	
			printf("%d ", deserialize(cur->value).num_steps);
			k++;
			                 //deserialize
  	}	
  	printf("] %d\n", k);
		
		k = 0;
		*/

		game = deserialize(remove_from_head(&l));
		/*
		printf("[ ");
  	for (struct list_node *cur = l.head; cur != NULL; cur = cur->next) {
    	
			printf("%d ", deserialize(cur->value).num_steps);
			k++;
			                 //deserialize
  	}	
  	printf("] %d\n\n", k);
		*/
		



		col = 0;
		row = 0;
		flag = 1;

		for(int i = 1; i < 17; i++)
		{
			//printf("%d = %d?\n", game.tiles[row][col], i);

			if((int) game.tiles[row][col] != i % 16)
			{
				flag = 0;
			}

			if(col == 4)
			{
				col = 0;
				row++;
			}
			
			col++;
			
		}
		
		
		//printf("flag: %d", flag);

		if(flag == 0)
		{
			//printf("test2\n");
			if((int) game.empty_row != 3)
			{
				newGame = copyGame(game);
				move_up(&newGame);

				serial = serialize(newGame);

				if(!searchList(tracker, serial))
				{
					insert_at_tail(&l, serial);
					insert_at_tail(&tracker, serial);
				}
			}

			if((int) game.empty_row != 0)
			{
				newGame = copyGame(game);
				move_down(&newGame);
				
				serial = serialize(newGame);

				if(!searchList(tracker, serial))
				{
					insert_at_tail(&l, serial);
					insert_at_tail(&tracker, serial);
				}

			}

			if((int) game.empty_col != 3)
			{
				newGame = copyGame(game);
				move_left(&newGame);
				
				serial = serialize(newGame);

				if(!searchList(tracker, serial))
				{
					insert_at_tail(&l, serial);
					insert_at_tail(&tracker, serial);
				}
	
			}

			if((int) game.empty_col != 0)
			{
				newGame = copyGame(game);
				move_right(&newGame);
				
				serial = serialize(newGame);

				if(!searchList(tracker, serial))
				{
					insert_at_tail(&l, serial);
					insert_at_tail(&tracker, serial);
				}
			}

		}

		//printf("test(2)");

	}
	
	while(!flag);

	//printf("test 3\n");

	free_list(l);
	free_list(tracker);

	return game.num_steps; 
}



#include "../Includes/fdf.h"
#include "../libft/libft.h"

t_list *create()
{
	t_list *new;

	new = (t_list *)malloc(sizeof(t_list));
	ft_bzero(new, sizeof(new));
	return (new);
}


int main(int argc, char **argv)
{
	t_list *list1;
	t_list *list2;
	t_list *list3;
	t_list *list4;
	t_list *head;
	t_list *tmp;

	printf("HERE\n");
	list1 = create();
	list1->content = (int *)1;
	list2 = create();
	list2->content = (int *)2;
	list3 = create();
	list3->content = (int *)3;
	
	head = list1;
	list1->next = list2;
	list2->next = list3;
	list3->next = NULL;

	while (head)
	{
		printf("HERE\n");
		printf("%d\n", (int)head->content);
		head = head->next;
	}
	return (0);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:58:39 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/03/20 15:10:39 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_support(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	void	*ptr;

	ptr = f(lst->content);
	result = ft_lstnew(ptr);
	if (!result)
	{
		del(ptr);
		return (0);
	}
	return (result);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*result;
	void	*ptr;

	if (!del || !f || !lst)
		return (NULL);
	result = ft_support(lst, f, del);
	if (!result)
		return (0);
	lst = lst->next;
	while (lst)
	{
		ptr = f(lst->content);
		temp = ft_lstnew(ptr);
		if (!temp)
		{
			del(ptr);
			ft_lstclear(&result, del);
			return (0);
		}
		ft_lstadd_back(&result, temp);
		lst = lst->next;
	}
	return (result);
}

/*
void *ft_f(void *s)
{

	char *test ; 
	test = "hit";
	(void)s;
	return ((void *)test);
}
void del(void *s)
{
	(void)s;
	return ;
}
int main(void)
{
	t_list *start;
	t_list *temp;


	start = ft_lstnew("test");
	ft_lstadd_back(&start, ft_lstnew("test2"));
	ft_lstadd_back(&start, ft_lstnew("test3"));
	ft_lstadd_back(&start, ft_lstnew("test3"));
	temp = start;
	printf("this is origin loop\n");
	while (temp)
	{
		printf("%s\n" , (char *)temp->content);
		temp = temp->next;
	}
	printf("this is map loop\n");
	temp = ft_lstmap(start, &ft_f, &del);
	while (temp)
	{
		printf("%s\n" , (char *)temp->content);
		temp = temp->next;
	}
	return 0;
}
	


*/

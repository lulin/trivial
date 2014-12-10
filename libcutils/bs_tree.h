/*
 * Copyright (c) 2014 GBCOM.,Ltd, Lulin Wang
 *
 * "License"(GPLv2)
 *
 * Bug reports and issues: <cnboywll@gmail.com> or <wanglulin@gbcom.com.cn>
 *
 * This file implements a binary search tree.
 */

#ifndef SEARCH_TREE_H_
#define SEARCH_TREE_H_

#include "list.h"

#include <assert.h>

/* Binary search tree */
struct bs_tree {
	struct bs_tree *parent;
	struct bs_tree *left;
	struct bs_tree *right;

	struct list_head stack;
};

#define bs_tree_init(name) {&(name), NULL, NULL}
#define init_bs_tree(t) do { \
	(t)->parent = (t); (t)->left = NULL; (t)->right = NULL; \
	INIT_LIST_HEAD(&(t)->stack);\
} while (0)

#define bs_tree_replace(oldtr, newtr)					\
	do {								\
		(newtr)->parent = (oldtr)->parent;			\
		(newtr)->left = (oldtr)->left;				\
		(newtr)->right = (oldtr)->right;			\
		if ((oldtr)->left) (oldtr)->left->parent = (newtr);	\
		if ((oldtr)->right) (oldtr)->right->parent = (newtr);	\
		if (bs_tree_isleft(oldtr))				\
			(oldtr)->parent->left = (newtr);		\
		else if (bs_tree_isroot(oldtr))				\
			(newtr)->parent = (newtr);			\
		else							\
			(oldtr)->parent->right = (newtr);		\
		init_bs_tree(oldtr);					\
	} while (0)

#define bs_tree_isroot(t)	((t)->parent == (t))
#define bs_tree_unrooted(t)	(!(t)->parent)
#define bs_tree_isleft(t)	((t)->parent && ((t) == (t)->parent->left))
#define bs_tree_isright(t)	((t)->parent && ((t) == (t)->parent->right))

#define bs_tree_entry(tree, type, member)	container_of(tree, type, member)
#define bs_tree_effect_root(root)		((root)->right)

#define bs_tree_foreach_inorder(root, pos, s)				\
	for (								\
		({							\
			if (bs_tree_isroot(root))			\
				pos = (root)->right;			\
			else						\
				pos = (root);				\
			if (pos && pos->right)				\
				list_add(&pos->right->stack, (s));	\
			if (pos && pos->left)				\
				list_add(&pos->left->stack, (s));	\
		});							\
		pos;							\
		({							\
			if (list_empty(s))				\
				pos = NULL;				\
			else {						\
				pos = container_of((s)->next,		\
					struct bs_tree, stack);		\
				list_del((s)->next);			\
				if (pos->right)				\
					list_add(&pos->right->stack, (s));\
				if (pos->left)				\
					list_add(&pos->left->stack, (s));\
			}						\
		})							\
	)

extern struct bs_tree *bs_tree_min(struct bs_tree *root);
extern struct bs_tree *bs_tree_max(struct bs_tree *root);

extern void bs_tree_trim(struct bs_tree *tree);

typedef int (*bst_comp_t)(struct bs_tree *, struct bs_tree *);

extern int bs_tree_insert(struct bs_tree *root, struct bs_tree *nt,
	bst_comp_t comp);

extern void bs_tree_del(struct bs_tree *tree);

extern struct bs_tree *bs_tree_search(struct bs_tree *root,
	struct bs_tree *key, bst_comp_t comp);

extern struct bs_tree *bs_tree_predecessor(struct bs_tree *tree);

extern struct bs_tree *bs_tree_successor(struct bs_tree *tree);

extern void bs_tree_findneighbor(struct bs_tree *root, struct bs_tree *key,
	struct bs_tree **ppred, struct bs_tree **psucc,
	bst_comp_t comp);

extern int bs_tree_addneighbor(struct bs_tree *root, struct bs_tree *pred,
	struct bs_tree *succ, struct bs_tree *nbr);

#endif /* SEARCH_TREE_H_ */

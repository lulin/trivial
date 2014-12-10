/*
 * Copyright (c) 2014 GBCOM.,Ltd, Lulin Wang
 *
 * "License"(GPLv2, since list.h is released under GPLv2)
 *
 * Bug reports and issues: <cnboywll@gmail.com> or <wanglulin@gbcom.com.cn>
 *
 * This file implements a binary search tree.
 */

#include "bs_tree.h"

#define __bs_tree_hangleft(tree, nt)\
	do {assert(!(tree)->left);\
	if (nt) {(nt)->parent = (tree); (tree)->left = (nt);}} while(0)

#define __bs_tree_hangright(tree, nt)\
	do {assert(!(tree)->right);\
	if (nt) {(nt)->parent = (tree); (tree)->right = (nt);}} while(0)

struct bs_tree *bs_tree_min(struct bs_tree *root)
{
	assert(root);
	struct bs_tree *pos, *min = NULL;

	if (bs_tree_isroot(root))
		pos = root->right;
	else
		pos = root;

	for (min = pos; pos; min = pos, pos = pos->left)
		;
	return min;
}

struct bs_tree *bs_tree_max(struct bs_tree *root)
{
	assert(root);
	struct bs_tree *pos, *max = NULL;

	if (bs_tree_isroot(root))
		pos = root->right;
	else
		pos = root;

	for (max = pos; pos; max = pos, pos = pos->right)
		;
	return max;
}

void bs_tree_trim(struct bs_tree *tree)
{
	if ((!tree) || bs_tree_isroot(tree))
		return ;

	if (bs_tree_isleft(tree))
		tree->parent->left = NULL;
	else
		tree->parent->right = NULL;

	return ;
}

static void __bs_tree_translate(struct bs_tree *old, struct bs_tree *nt)
{
	assert(old);

	if (nt)
		nt->parent = old->parent;

	if (bs_tree_isleft(old))
		old->parent->left = nt;
	else	/* the old tree is root or right child. */
		old->parent->right = nt;

//	old->parent = old;
//	old->left = NULL;
//	old->right = NULL;
	return;
}

int bs_tree_insert(struct bs_tree *root, struct bs_tree *nt,
	bst_comp_t comp)
{
	assert(root);
	assert(nt);
	assert(comp);
	assert(bs_tree_isroot(root));

	if (root->right == NULL) {
		__bs_tree_hangright(root, nt);
		return 0;
	}

	struct bs_tree *pos;
	for (pos = root->right;;) {
		int r = comp(nt, pos);
		if (r < 0) {
			if (!pos->left) {
				__bs_tree_hangleft(pos, nt);
				return 0;
			}
			pos = pos->left;
		} else if (r > 0) {
			if (!pos->right) {
				__bs_tree_hangright(pos, nt);
				return 0;
			}
			pos = pos->right;
		} else {
			struct bs_tree *right = pos->right;
			bs_tree_trim(right);
			__bs_tree_hangright(pos, nt);
			__bs_tree_hangright(nt, right);
			return 0;
		}
	}

	return 0;
}

void bs_tree_del(struct bs_tree *tree)
{
	struct bs_tree *tleft = tree->left;
	struct bs_tree *tright = tree->right;

	if (!tree)
		return;

	if (bs_tree_isroot(tree))
		return;

	if (!tleft) {
		__bs_tree_translate(tree, tright);
		init_bs_tree(tree);
		return ;
	}

	if (!tright) {
		__bs_tree_translate(tree, tleft);
		init_bs_tree(tree);
		return ;
	}

	if (!tright->left) {
		__bs_tree_translate(tree, tright);
		__bs_tree_hangleft(tright, tleft);
		init_bs_tree(tree);
		return ;
	}

	struct bs_tree *min = bs_tree_min(tright);

	__bs_tree_translate(min, min->right);
	__bs_tree_hangright(min, tright);
	__bs_tree_translate(tree, min);
	__bs_tree_hangleft(min, tleft);

	init_bs_tree(tree);
	return;
}

struct bs_tree *bs_tree_search(struct bs_tree *root,
	struct bs_tree *kt, bst_comp_t comp)
{
	assert(root);
	assert(kt);
	assert(comp);
	struct bs_tree *pos;

	if (bs_tree_isroot(root))
		pos = root->right;
	else
		pos = root;

	for (; pos;) {
		int r = comp(kt, pos);
		if (r < 0)
			pos = pos->left;
		else if (r > 0)
			pos = pos->right;
		else
			break;
	}

	return pos;
}

struct bs_tree *bs_tree_predecessor(struct bs_tree *tree)
{
	if (!tree)
		return NULL;

	if (bs_tree_isroot(tree))
		return NULL;

	if (tree->left)
		return bs_tree_max(tree->left);

	if (bs_tree_isright(tree)) {
		if (bs_tree_isroot(tree->parent))
			return NULL;
		return tree->parent;
	}

	/* is left child */
	struct bs_tree *pos;
	for (pos = tree->parent; !bs_tree_isroot(pos); pos = pos->parent) {
		if (bs_tree_isright(pos)) {
			if (bs_tree_isroot(pos->parent))
				return NULL;
			return pos->parent;
		}
	}
	return NULL;
}

struct bs_tree *bs_tree_successor(struct bs_tree *tree)
{
	if (!tree)
		return NULL;

	if (bs_tree_isroot(tree))
		return NULL;

	if (tree->right)
		return bs_tree_min(tree->right);

	if (bs_tree_isleft(tree))
		return tree->parent;

	/* is right child */
	struct bs_tree *pos;
	for (pos = tree->parent; !bs_tree_isroot(pos); pos = pos->parent) {
		if (bs_tree_isleft(pos))
			return pos->parent;
	}
	return NULL;
}

void bs_tree_findneighbor(struct bs_tree *root,
	struct bs_tree *key, struct bs_tree **ppred, struct bs_tree **psucc,
	bst_comp_t comp)
{
	assert(root);
	assert(key);
	assert(comp);

	struct bs_tree *predecessor = NULL;
	struct bs_tree *successor = NULL;

	struct bs_tree *pos;
	for (pos = root->right; pos;) {
		int r = comp(key, pos);
		if (r < 0) {
			successor = pos;
			pos = pos->left;
		} else if (r > 0) {
			predecessor = pos;
			pos = pos->right;
		} else {    /* equal */
			predecessor = pos;
			successor = pos;
			break;
		}
	}

	if (ppred)
		*ppred = predecessor;
	if (psucc)
		*psucc = successor;
	return ;
}

int bs_tree_addneighbor(struct bs_tree *root, struct bs_tree *pred,
	struct bs_tree *succ, struct bs_tree *nbr)
{
	assert(root);
	assert(nbr);

	if (!pred) {
		if (!succ)
			__bs_tree_hangright(root, nbr);
		else
			__bs_tree_hangleft(succ, nbr);
		return 0;
	}

	if (!succ) {
		assert(!pred->right);
		__bs_tree_hangright(pred, nbr);
		return 0;
	}

	if (pred == succ) {
		struct bs_tree *tright = pred->right;
		bs_tree_trim(tright);
		__bs_tree_hangright(pred, nbr);
		__bs_tree_hangright(nbr, tright);
		return 0;
	}

	if (!pred->right)
		__bs_tree_hangright(pred, nbr);
	else {
		assert(!succ->left);
		__bs_tree_hangleft(succ, nbr);
	}

	return 0;
}


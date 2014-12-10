/*
 * Copyright (c) 2014
 *
 * "License"
 *
 * Bug reports and issues: <"Email">
 *
 * This file is part of cwfragment.
 */

#include "bs_tree.h"
#include "list.h"
#include <stdio.h>
#include <assert.h>

struct test_tr {
	int data;
	struct bs_tree tree;
};

int test_cmp(struct bs_tree *t1, struct bs_tree *t2)
{
	struct test_tr *tt1, *tt2;
	tt1 = container_of(t1, struct test_tr, tree);
	tt2 = container_of(t2, struct test_tr, tree);

	return tt1->data - tt2->data;
}

void test_bs_tree_search(struct bs_tree *root)
{
	printf("Test bs_tree_search:\n");

	int k[] = {53, 109, 10, 110, 77, 88, 23, 8};
	struct test_tr tt;
	init_bs_tree(&tt.tree);
	struct bs_tree *r;
	int i;

	for (i = 0; i < sizeof(k)/sizeof(k[0]); i++) {
		tt.data = k[i];
		struct test_tr *ttr;
		struct test_tr *ttrp;
		r = bs_tree_search(root, &tt.tree, test_cmp);
		if (r) {
			ttr = container_of(r, struct test_tr, tree);

			if (!bs_tree_isroot(r->parent))
			ttrp = container_of(r->parent, struct test_tr, tree);
			else
				ttrp = NULL;

			printf("Search %d,\tbingo!\t Parent: %d\n",
				ttr->data, ttrp? ttrp->data: 0);
		} else
			printf("Search %d,\tmiss!\n", tt.data);
	}
}

void test_bs_tree_foreach_inorder(struct bs_tree *root)
{
	printf("In-order traverse the tree:\n");

	struct bs_tree *pos;
	struct test_tr *conpos, *conparent;
	LIST_HEAD(stack);

	bs_tree_foreach_inorder(root, pos, &stack) {
		conpos = container_of(pos, struct test_tr, tree);
		conparent = container_of(pos->parent, struct test_tr, tree);

		if (bs_tree_isroot(pos->parent))
			printf("Root: %d\n", conpos->data);
		else if (pos == pos->parent->left)
			printf("L: %d\tP: %d\n", conpos->data, conparent->data);
		else if (pos == pos->parent->right)
			printf("R: %d\tP: %d\n", conpos->data, conparent->data);
	}

	return;
}

void test_bs_tree_del(struct bs_tree *tree)
{
	printf("Test bs_tree_del, detele %d:",
		container_of(tree, struct test_tr, tree)->data);
	bs_tree_del(tree);
	printf("\tDone!\n");
	return ;
}

void test_bs_tree_findneighbor(struct bs_tree *root)
{
	struct test_tr tr;
	struct test_tr *epred, *esucc;
	struct bs_tree *pred, *succ;
	init_bs_tree(&tr.tree);

	int i;
	int k[] = {100, 53, 99, 180, 20, 17, 49};
	for (i = 0; i < sizeof(k)/sizeof(k[0]); i++) {
		tr.data = k[i];
		bs_tree_findneighbor(root, &tr.tree, &pred, &succ, test_cmp);
		epred = pred? container_of(pred, struct test_tr, tree): NULL;
		esucc = succ? container_of(succ, struct test_tr, tree): NULL;
		printf("New comer: %d,\tPredecessor: %d,\tSuccessor: %d\n",
			tr.data, epred? epred->data: 0, esucc? esucc->data: 9999999);
	}
	return;
}

void test_bs_tree_predecessor(struct bs_tree *tree)
{
	struct test_tr *epred;
	struct bs_tree *pred;

	pred = bs_tree_predecessor(tree);
	epred = pred? container_of(pred, struct test_tr, tree): NULL;
	printf("Predecessor of %4d is:\t %d\n",
		container_of(tree, struct test_tr, tree)->data,
		epred? epred->data: 0);
	return;
}

void test_bs_tree_successor(struct bs_tree *tree)
{
	struct test_tr *esucc;
	struct bs_tree *succ;

	succ = bs_tree_successor(tree);
	esucc = succ? container_of(succ, struct test_tr, tree): NULL;
	printf("Successor of %4d is:\t %d\n",
		container_of(tree, struct test_tr, tree)->data,
		esucc? esucc->data: 99999);
	return;
}

void test_bs_tree_addneighbor(struct bs_tree *root)
{
	struct bs_tree *pred, *succ;
	struct bs_tree *nbr;
	struct test_tr *enbr;
	int k[] = {8, 23, 99, 76, 53, 37, 260};
	int i;

	printf("Test add neighbor:\n");

	for (i = 0; i < sizeof(k)/sizeof(k[0]); i++) {
		enbr = malloc(sizeof(struct test_tr));
		init_bs_tree(&enbr->tree);
		enbr->data = k[i];
		nbr = &enbr->tree;

		printf("Add %d\n", enbr->data);
		bs_tree_findneighbor(root, nbr, &pred, &succ, test_cmp);
		bs_tree_addneighbor(root, pred, succ, nbr);
	}
	test_bs_tree_foreach_inorder(root);
	return;
}

int main(int argc, char *argv[])
{
	struct bs_tree *root, _root;

	struct test_tr *t1, *t2, *t3, *t4, *t5;
	struct test_tr *t6, *t7, *t8, *t9, *t0;
	t1 = calloc(1, sizeof(struct test_tr));
	t2 = calloc(1, sizeof(struct test_tr));
	t3 = calloc(1, sizeof(struct test_tr));
	t4 = calloc(1, sizeof(struct test_tr));
	t5 = calloc(1, sizeof(struct test_tr));
	t6 = calloc(1, sizeof(struct test_tr));
	t7 = calloc(1, sizeof(struct test_tr));
	t8 = calloc(1, sizeof(struct test_tr));
	t9 = calloc(1, sizeof(struct test_tr));
	t0 = calloc(1, sizeof(struct test_tr));

	root = &_root;
	init_bs_tree(root);
	init_bs_tree(&t1->tree);
	init_bs_tree(&t2->tree);
	init_bs_tree(&t3->tree);
	init_bs_tree(&t4->tree);
	init_bs_tree(&t5->tree);
	init_bs_tree(&t6->tree);
	init_bs_tree(&t7->tree);
	init_bs_tree(&t8->tree);
	init_bs_tree(&t9->tree);
	init_bs_tree(&t0->tree);

	t1->data = 77;
	t2->data = 106;
	t3->data = 10;
	t4->data = 53;
	t5->data = 30;
	t6->data = 9;
	t7->data = 23;
	t8->data = 11;
	t9->data = 57;
	t0->data = 110;

	bs_tree_insert(root, &t1->tree, test_cmp);
	bs_tree_insert(root, &t2->tree, test_cmp);
	bs_tree_insert(root, &t3->tree, test_cmp);
	bs_tree_insert(root, &t4->tree, test_cmp);
	bs_tree_insert(root, &t5->tree, test_cmp);
	bs_tree_insert(root, &t6->tree, test_cmp);
	bs_tree_insert(root, &t7->tree, test_cmp);
	bs_tree_insert(root, &t8->tree, test_cmp);
	bs_tree_insert(root, &t9->tree, test_cmp);
	bs_tree_insert(root, &t0->tree, test_cmp);

	int i;
	for (i = 0; i < 8; i++) {
		struct test_tr *tr = malloc(sizeof(struct test_tr));
		init_bs_tree(&tr->tree);
		tr->data = i/2 + (i+1)/2 + (i+3)/2 + 47;
		bs_tree_insert(root, &tr->tree, test_cmp);
	}

	test_bs_tree_foreach_inorder(root);
	printf("----\n");

	test_bs_tree_search(root);
	printf("----\n");

	test_bs_tree_predecessor(&t8->tree);
	test_bs_tree_predecessor(&t4->tree);
	test_bs_tree_predecessor(&t7->tree);
	test_bs_tree_predecessor(&t6->tree);
	test_bs_tree_predecessor(&t3->tree);
	printf("----\n");

	test_bs_tree_successor(&t1->tree);
	test_bs_tree_successor(&t2->tree);
	test_bs_tree_successor(&t9->tree);
	test_bs_tree_successor(&t0->tree);
	test_bs_tree_successor(&t5->tree);
	printf("----\n");

	test_bs_tree_del(&t0->tree);
	test_bs_tree_del(&t3->tree);
	test_bs_tree_del(&t4->tree);
	test_bs_tree_del(&t9->tree);
	test_bs_tree_del(&t5->tree);
	test_bs_tree_foreach_inorder(root);
	printf("----\n");

	test_bs_tree_findneighbor(root);
	printf("----\n");

	test_bs_tree_addneighbor(root);
	return 0;
}


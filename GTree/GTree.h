#ifndef GTREE_H
#define GTREE_H

typedef void GTree;
typedef void GTreeData;

typedef void (*PrintFunc)(GTreeData* data);

GTree* GTree_Create();

void GTree_Clear(GTree* tree);

void GTree_Destroy(GTree* tree);

int GTree_Insert(GTree* tree, GTreeData* data, int pPos);

GTreeData* GTree_Delete(GTree* tree, int pos);

GTreeData* GTree_Get(GTree* tree, int pos);

int GTree_Count(GTree* tree);

GTreeData* GTree_Root(GTree* tree);

int GTree_Height(GTree* tree);

int GTree_Degree(GTree* tree);

void GTree_Display(GTree* tree, PrintFunc printFunc);

void GTree_Search(GTree* tree, GTreeData* data, PrintFunc printFunc);

#endif

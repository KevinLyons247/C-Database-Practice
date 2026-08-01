# SQLite Clone in C

> A lightweight relational database built completely in C from scratch, inspired by SQLite's internal architecture.

<p align="center">
  <img src="images/database-architecture.png" width="700"/>
</p>

---

## Overview

This project recreates the core components of a relational database engine without relying on external libraries. Rather than focusing solely on SQL syntax, the goal of this project was to understand how databases actually store, organize, and retrieve data efficiently.

The database supports:

- SQL-like `INSERT` and `SELECT` statements
- Persistent on-disk storage
- Fixed-size page management
- B+ Tree storage engine
- Binary search for fast lookups
- Automatic node splitting
- Duplicate key detection
- Interactive command-line interface

---

# Architecture

The database is divided into several layers similar to SQLite.

<p align="center">
  <img src="images/database-architecture.png" width="700"/>
</p>

```
SQL Input
     │
     ▼
SQL Parser
     │
     ▼
Virtual Machine
     │
     ▼
B+ Tree
     │
     ▼
Pager
     │
     ▼
Database File
```

### SQL Processor

The SQL processor parses commands entered by the user such as:

```sql
insert 1 Kevin kevin@gmail.com
select
```

and converts them into executable statements.

---

### Virtual Machine

The virtual machine executes parsed SQL statements and interacts directly with the storage engine.

---

### Pager

The pager manages communication between memory and disk.

Instead of loading the entire database into memory, the pager loads fixed-size **4096-byte pages** only when they are needed. Modified pages are written back to disk when the database closes.

This design allows databases to efficiently work with files much larger than available RAM.

---

# B+ Tree Storage Engine

<p align="center">
  <img src="images/btree-growth.png" width="650"/>
</p>

The B+ Tree is the primary data structure used to organize records inside the database.

SQLite stores both tables and indexes using B-Trees because they provide:

- **O(log n)** search performance
- Fast insertions and deletions
- Efficient range queries
- Balanced tree height
- Excellent disk locality

Unlike a binary search tree, every node can contain multiple keys and multiple child pointers.

This dramatically reduces the height of the tree, minimizing expensive disk reads.

---

# B-Tree vs B+ Tree

SQLite actually uses **B-Trees** for indexes and a variation called a **B+ Tree** for tables.

| Feature | B-Tree | B+ Tree |
|---------|---------|----------|
| Used for | Indexes | Tables |
| Internal nodes store keys | ✅ | ✅ |
| Internal nodes store values | ✅ | ❌ |
| Leaf nodes store values | ✅ | ✅ |
| Range scans | Good | Excellent |
| Number of child pointers | Fewer | More |

In this project, the storage engine is implemented as a **B+ Tree**, where **only the leaf nodes store complete database rows**.

Internal nodes are used exclusively for routing searches to the correct leaf node.

---

# Internal Nodes vs Leaf Nodes

| Internal Node | Leaf Node |
|---------------|-----------|
| Stores separator keys | Stores complete rows |
| Stores child page numbers | Stores key/value pairs |
| Routes searches | Holds actual data |
| No row data | Database records |

Because internal nodes only contain keys and pointers, they can fit many more entries inside a page, reducing the overall tree height.

---

# How the B+ Tree Grows

## Step 1

The database begins with a single leaf node.

```
[7 16]
```

---

## Step 2

When the leaf becomes full, inserting another record causes it to split.

```
Before:

[7 16 20]

After:

[7]
[16 20]
```

A new parent node is created to separate the two leaf pages.

---

## Step 3

Additional insertions continue splitting leaf nodes whenever they become full.

<p align="center">
  <img src="images/root-split.png" width="650"/>
</p>

If the parent node also becomes full, the split propagates upward.

---

## Step 4

Eventually the root node must split.

When this happens:

- Two internal nodes are created
- A brand new root is created
- The height of the tree increases by one

One of the most important concepts I learned is that **the height of a B+ Tree only increases when the root node splits**.

Every other split simply redistributes keys while keeping the tree balanced.

---

# Why Databases Use B+ Trees

Compared to other data structures:

✅ Fast searches (**O(log n)**)

✅ Fast insertions

✅ Fast deletions

✅ Efficient range scans

✅ Balanced tree height

✅ Optimized for disk storage

Unlike hash tables, B+ Trees preserve sorted order, making queries like:

```sql
SELECT * WHERE id BETWEEN 1000 AND 2000;
```

very efficient.

---

# What I Learned

Building this project taught me significantly more than SQL syntax.

## Data Structures

- B+ Trees
- Binary Search
- Tree Traversal
- Tree Balancing
- Node Splitting
- Internal vs Leaf Nodes

## Systems Programming

- Manual memory management
- Pointer arithmetic
- Struct memory layout
- Serialization
- Deserialization

## Storage Engines

- Fixed-size pages
- Disk persistence
- Buffer management
- Page caching

## Algorithms

- Binary Search
- Ordered insertion
- Recursive traversal
- Root splitting
- Duplicate key detection

## Operating Systems

- File I/O
- Persistent storage
- Low-level memory management
- Page-oriented architecture

---

# Example

```text
db > insert 1 Kevin kevin@gmail.com
Executed.

db > insert 2 Alice alice@gmail.com
Executed.

db > select

(1, Kevin, kevin@gmail.com)
(2, Alice, alice@gmail.com)
```

---

# Features

- ✅ SQL-like interface
- ✅ Persistent database file
- ✅ Pager implementation
- ✅ B+ Tree storage engine
- ✅ Binary search
- ✅ Automatic leaf node splitting
- ✅ Internal node splitting
- ✅ Root splitting
- ✅ Duplicate key detection
- ✅ Ordered record storage

---

# Technologies

- C
- Data Structures
- Algorithms
- File I/O
- Systems Programming
- Memory Management

---

# Future Improvements

- Delete statements
- Secondary indexes
- Transactions
- Write-Ahead Logging (WAL)
- Query optimizer
- Concurrency support
- Variable-length records

---

# References

- SQLite Architecture
- SQLite Documentation
- "Let's Build a Simple Database" by cstack
- Introduction to B+ Trees

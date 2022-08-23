# ps1-lisp
A very simple lisp, suitable for embedding. 

### Features
- No use of malloc() or other system calls, ideal for `-ffreestanding`
- Mark-and-sweep garbage collector 
- Efficient slab allocator implementation for cons and value cells

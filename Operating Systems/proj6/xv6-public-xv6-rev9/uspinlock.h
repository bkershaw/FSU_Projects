
struct uspinlock{
  uint locked;
};
void uinitlock (struct uspinlock *lock);
void uacquire  (struct uspinlock *lock);
void urelease  (struct uspinlock *lock);

int egy()
{
  if (readValue == BLACK) {
    printf("BLACK");
  } else if (readValue == WHITE) {
    printf("WHITE");
  }
  /* ... */
}

int masik()
{
  switch (readValue)
  {
    case BLACK:
      printf("BLACK");
      break;
    case WHITE:
      printf("WHITE");
      break;
    /* ... */
    default:
      printf("Hulyeseget irtal be...");
      //break;
  }
}
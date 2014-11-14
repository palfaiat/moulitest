char 	*line;
int		out;
int		p[2];
int		fd;

line = malloc(99999);
out = dup(1);
pipe(p);

fd = 1;
dup2(p[1], fd);
write(fd, "\naaa\nbbb\n", 12);
dup2(out, fd);
get_next_line(p[0], &line);
UT_ASSERT_EQ(strcmp(line, ""), 0);
get_next_line(p[0], &line);
UT_ASSERT_EQ(strcmp(line, "aaa"), 0);
get_next_line(p[0], &line);
UT_ASSERT_EQ(strcmp(line, "bbb"), 0);

fd = 0;
dup2(p[1], fd);
write(fd, "aaa\n", 12);
dup2(out, fd);
get_next_line(p[0], &line);
UT_ASSERT_EQ(strcmp(line, "aaa"), 0);

fd = 1;
dup2(p[1], fd);
write(fd, "aaa\n", 12);
dup2(out, fd);
get_next_line(p[0], &line);
UT_ASSERT_EQ(strcmp(line, "aaa"), 0);
#Compiler and Linker
CC          := cc

#The Target library
TARGET      := get_next_line.a

#The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := src
INCDIR      := inc
BUILDDIR    := obj
TARGETDIR   := lib
RESDIR      := res
SRCEXT      := c
OBJEXT      := o

#Flags, Libraries and Includes
CFLAGS      := -Wall -Werror -Wextra

#---------------------------------------------------------------------------------
#DO NOT EDIT BELOW THIS LINE
#---------------------------------------------------------------------------------
SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))
OBJS        := $(shell find $(BUILDDIR) -type f -name *.$(OBJEXT))

#Default Make
all: directories $(TARGET)

#Remake
re: fclean all

#Make the Directories
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

#Clean only Objects
clean:
	@$(RM) -rf $(BUILDDIR)

#Full Clean, Objects and Binaries
fclean: clean
	@$(RM) -rf $(TARGETDIR)

#Link
$(TARGET): $(OBJECTS)
	@if [ ! -f $(TARGET) ]; ar rcs $(TARGET) $(OBJECTS); then mv $(TARGET) $(TARGETDIR)/l; fi

#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

#Non-File Targets
.PHONY: all re clean fclean 

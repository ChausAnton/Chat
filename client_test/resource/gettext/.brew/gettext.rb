class Gettext < Formula
  desc "GNU internationalization (i18n) and localization (l10n) library"
  homepage "https://www.gnu.org/software/gettext/"
  url "https://ftp.gnu.org/gnu/gettext/gettext-0.21.tar.xz"
  mirror "https://ftpmirror.gnu.org/gettext/gettext-0.21.tar.xz"
  sha256 "d20fcbb537e02dcf1383197ba05bd0734ef7bf5db06bdb241eb69b7d16b73192"
  license "GPL-3.0-or-later"

  livecheck do
    url :stable
  end

  uses_from_macos "libxml2"
  uses_from_macos "ncurses"

  def install
    args = [
      "--disable-dependency-tracking",
      "--disable-silent-rules",
      "--disable-debug",
      "--prefix=#{prefix}",
      "--with-included-glib",
      "--with-included-libcroco",
      "--with-included-libunistring",
      "--with-included-libxml",
      "--with-emacs",
      "--with-lispdir=#{elisp}",
      "--disable-java",
      "--disable-csharp",
      # Don't use VCS systems to create these archives
      "--without-git",
      "--without-cvs",
      "--without-xz",
    ]
    on_macos do
      # Ship libintl.h. Disabled on linux as libintl.h is provided by glibc
      # https://gcc-help.gcc.gnu.narkive.com/CYebbZqg/cc1-undefined-reference-to-libintl-textdomain
      # There should never be a need to install gettext's libintl.h on
      # GNU/Linux systems using glibc. If you have it installed you've borked
      # your system somehow.
      args << "--with-included-gettext"
    end
    on_linux do
      args << "--with-libxml2-prefix=#{Formula["libxml2"].opt_prefix}"
    end
    system "./configure", *args
    system "make"
    ENV.deparallelize # install doesn't support multiple make jobs
    system "make", "install"
  end

  test do
    system bin/"gettext", "test"
  end
end

#
# Cookbook Name:: development
# Recipe:: default
#
# Copyright 2015, south37
#
# All rights reserved - Do Not Redistribute
#

package 'git' do
  action :install
end

package 'vim' do
  action :install
end

package 'g++' do
  action :install
end

package 'libtool' do
  action :install
end

package 'm4' do
  action :install
end

package 'autoconf' do
  action :install
end

package 'texinfo' do
  action :install
end

remote_file "/tmp/llvm-3.7.0.src.tar.xz" do
  source "http://llvm.org/releases/3.7.0/llvm-3.7.0.src.tar.xz"
end

remote_file "/tmp/cfe-3.7.0.src.tar.xz" do
  source "http://llvm.org/releases/3.7.0/cfe-3.7.0.src.tar.xz"
end

remote_file "/tmp/compiler-rt-3.7.0.src.tar.xz" do
  source "http://llvm.org/releases/3.7.0/compiler-rt-3.7.0.src.tar.xz"
end

home_dir = "/home/vagrant"
llvm_dir = "#{home_dir}/llvm"
clang_dir = "#{llvm_dir}/llvm-3.7.0.src/tools/clang/"
compiler_rt_dir = "#{llvm_dir}/llvm-3.7.0.src/projects/compiler-rt/"
build_dir = "#{llvm_dir}/llvm-build"
script "install llvm" do
  interpreter "bash"
  user        "vagrant"
  code <<-EOL
    mkdir #{llvm_dir}
    tar Jxf /tmp/llvm-3.7.0.src.tar.xz -C #{llvm_dir}
    mkdir #{clang_dir}
    tar Jxf /tmp/cfe-3.7.0.src.tar.xz -C #{clang_dir}
    mkdir #{compiler_rt_dir}
    tar Jxf /tmp/compiler-rt-3.7.0.src.tar.xz -C #{compiler_rt_dir}
    mkdir #{build_dir}
    cd #{build_dir}
    ../llvm-3.7.0.src/configure --prefix=/usr/local/llvm --enable-optimized
    make -j2
    make check
    sudo make install
  EOL
end

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

llvm_32 = "http://llvm.org/releases/3.2/"
llvm = "llvm-3.2.src.tar.gz"
clang = "clang-3.2.src.tar.gz"
compiler_rt = "compiler-rt-3.2.src.tar.gz"
remote_file "/tmp/#{llvm}" do
  source "#{llvm_32}#{llvm}"
end

remote_file "/tmp/#{clang}" do
  source "#{llvm_32}#{clang}"
end

remote_file "/tmp/#{compiler_rt}" do
  source "#{llvm_32}#{compiler_rt}"
end

home_dir = "/home/vagrant"
llvm_dir = "#{home_dir}/llvm/llvm-3.2.src"
clang_dir = "#{llvm_dir}/tools/clang/"
compiler_rt_dir = "#{llvm_dir}/projects/compiler-rt/"
build_dir = "#{llvm_dir}/llvm-build"
script "install llvm" do
  interpreter "bash"
  user        "vagrant"
  code <<-EOL
    mkdir -p #{llvm_dir}
    tar xzf /tmp/#{llvm} -C #{llvm_dir}
    mkdir #{clang_dir}
    tar xzf /tmp/#{clang} -C #{clang_dir}
    mkdir #{compiler_rt_dir}
    tar xzf /tmp/#{compiler_rt} -C #{compiler_rt_dir}
    mkdir #{build_dir}
    cd #{build_dir}
    ../llvm-3.2.src/configure --prefix=/usr/local/llvm --enable-optimized
    make -j2
    make check
    sudo make install
    echo 'export PATH=$PATH:/usr/local/llvm/bin' >> ~/.bashrc
  EOL
end

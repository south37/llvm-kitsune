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

directory "~/llvm" do
  owner "vagrant"
  group "vagrant"
  recursive true
  mode 0755
  action :create
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

script "install_wordpress" do
  interpreter "bash"
  user        "vagrant"
  code <<-EOL
    tar Jxf /tmp/llvm-3.7.0.src.tar.xz -C ~/llvm
    mkdir ~/llvm/llvm-3.7.0.src/tools/clang
    tar Jxf /tmp/cfe-3.7.0.src.tar.xz -C ~/llvm/llvm-3.7.0.src/tools/clang
    mkdir ~/llvm/llvm-3.7.0.src/projects/compiler-rt
    tar Jxf /tmp/compiler-rt-3.7.0.src.tar.xz -C ~/llvm/llvm-3.7.0.src/projects/compiler-rt
  EOL
end

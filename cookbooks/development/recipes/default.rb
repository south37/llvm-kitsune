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

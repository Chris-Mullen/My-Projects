#  frozen_string_literal: true

Rails.application.routes.draw do
  get 'genres/show'
  get 'artists/show'
  get 'albums/show'
  get 'songs/create'
  get 'songs/update'
  get 'songs/destroy'
  get 'songs/show'
  # For details on the DSL available within this file, see https://guides.rubyonrails.org/routing.html
end

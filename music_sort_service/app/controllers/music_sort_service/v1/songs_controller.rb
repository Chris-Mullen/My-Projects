#  frozen_string_literal: true

module MusicSortService
  module V1
    # Controller for managing songs
    class SongsController < ApplicationController
      def create
        album = Album.where(title: params[:album]).first
        unless album
          render_json_not_found_error('album', params[:album])
          return
        end

        genre = Genre.where(title: params[:genre]).first
        unless genre
          render_json_not_found_error('genre', params[:genre])
          return
        end

        song = Song.create_song(params, album.uuid, genre.uuid)
        unless song.save
          render_json_validation_error(song)
          return
        end

        render json: song, status: :created
      end

      def update; end

      def destroy; end

      def show; end
    end
  end
end

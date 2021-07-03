#  frozen_string_literal: true

module MusicSortService
  module V1
    # Controller for managing albums
    class AlbumsController < ApplicationController
      def create
        album = Album.new(album_params)
        unless album.save
          render_json_validation_error(album)
          return
        end

        render json: album, status: :created
      end

      def show
        render json: Album.where(uuid: params[:album_id])
      end

      def show_all; end

      private

      def album_params
        params.require(:album).permit(:title, :year, :tracks, :disks)
      end
    end
  end
end

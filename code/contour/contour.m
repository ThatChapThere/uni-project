leaf_types = ["cordate" "cuneate" "deltoid" "elliptic" "hastate" ...
    "lanceolate" "linear" "obcordate" "obdeltoid" "oblanceolate" ...
    "oblong" "obovate" "orbiculate" "ovate" "peltate" "reniform" ...
    "rhombic" "sagitate" "spathulate" "subulate"
];

for leaf_type = leaf_types
    leaf_image = imread(strcat("original/", leaf_type, '.png'));

    % Convert image to grayscale and binarise
    leaf_image = im2gray(leaf_image);
    leaf_image = imbinarize(leaf_image);

    % Binarisation makes the values 1 and 0,
    % multiplying by 255 makes it a standard black and white image
    leaf_image = 255 * leaf_image;

    % Write the binarised image to a file
    imwrite(leaf_image, strcat("binarised/", leaf_type, ".png"));

    % Create a mask for and active contour,
    % this is a black binary image with a white border
    contour_mask = zeros(size(leaf_image));
    contour_border_thickness = 15;
    contour_mask( ...
        contour_border_thickness:end-contour_border_thickness, ...
        contour_border_thickness:end-contour_border_thickness ...
    ) = 1;

    % Apply an active contour to the binarised leaf image,
    % and save the result
    leaf_contour = activecontour(leaf_image, contour_mask, 1000, "edge");
    imwrite(leaf_contour, strcat("contour_mask/", leaf_type, ".png"));

    % Find the boundary of the image as a set of points,
    % and save to a csv file
    leaf_boundary = bwboundaries(leaf_contour, "noholes");
    leaf_boundary = leaf_boundary{1};
    writematrix(leaf_boundary, strcat("csv/", leaf_type, ".csv"));

    % Save the contour to an image so that it can be checked for any issues
    plot(leaf_boundary(:,2), -leaf_boundary(:,1));
    axis equal;
    saveas(gcf, strcat("contour/", leaf_type, ".png"))
end